/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Game
*/

#include "Game.hpp"
#include "Communication.hpp"
#include "TransformPath.hpp"

Game::Game()
    : _level(0), _score(0)
{
    _init = false;
}

Game::~Game()
{
}

void Game::run(std::shared_ptr<Server> server)
{
    boost::posix_time::milliseconds ms(100);
    boost::asio::deadline_timer t(server->getIoService(), ms);
    if (!is_running(0))
        return;
    t.expires_at(t.expires_at() + ms);
    t.async_wait(
        [this, &server](const boost::system::error_code &error) {
            static int timerCount = 29;
            Communication::Timer timer;
            int status = server->getGameStatus();

            timer.time = (int)timerCount / 5;
            if (!error) {
                if (status == 0) {
                    timerCount = 29;
                    this->run(server);
                }
                else if (status == 1) {
                    server->sendToAll(timer);
                    timerCount--;
                    if (timerCount == 0) {
                        server->setGameStatus(2);
                        timerCount = 29;
                    }
                }
                if (status == 2) {
                    if (!_init)
                        initGame(transformPath(std::string("assets/test.json")));
                    server->sendToAll(timer);
                }
            }
            if (!is_running(0))
                return;
            this->run(server);
        });
    server->getIoService().run();
}

void Game::setLevel(int level)
{
    _level = level;
}

void Game::setScore(int score)
{
    _score = score;
}

int Game::getLevel() const
{
    return _level;
}

int Game::getScore() const
{
    return _score;
}

void Game::initGame(std::string map_path)
{
    _init = true;
    int _last_entity_id = 0;
    Parser::ParserJson parser = Parser::ParserJson(map_path).parse();
    _entities = parser.getEntities();
    _tile_size = parser.getTileSize();
    for (auto &entity : _entities) {
        if (Parser::keyExists(entity.instance, "id") && (entity.id) > _last_entity_id) {
            _last_entity_id = entity.id;
        }
    }
}

void Game::updateGame(std::shared_ptr<Server> server)
{
    for (auto &entity : _entities) {
        updateShips(server, entity);
        updateColisions(server, entity);
        updateEntities(server, entity);
    }
    // sendBullets(server);
    sendShips(server);
    sendBonus(server);
    _bullets.clear();
    _ships.clear();
    _bonus.clear();
    _loop++;
}

void Game::updateShips(std::shared_ptr<Server> server, Parser::entity_t &entity)
{
    int index = 0;
    for (auto &communication : server->getInput()) {
        for (int i = 0; i < communication.second.nbrItems; i++) {
            if (entity.type == "__player__" && entity.id == communication.first) {
                if (entity.instance.find("speed") == entity.instance.end()) {
                    Parser::setValue(entity.instance, "speed", 1.0);
                }
                for (int i = 0; i < communication.second.nbrItems; i++) {
                    switch (communication.second.event[i]) {
                        case Communication::EventInput::Key_up:
                            Parser::setValue(entity.instance, std::string("y"), (float)((entity.instance["y"].getFloat()) - 20 * (entity.instance["speed"].getFloat())));
                            break;
                        case Communication::EventInput::Key_down:
                            Parser::setValue(entity.instance, std::string("y"), (float)((entity.instance["y"].getFloat()) + 20 * (entity.instance["speed"].getFloat())));
                            break;
                        case Communication::EventInput::Key_left:
                            Parser::setValue(entity.instance, std::string("x"), (float)((entity.instance["x"].getFloat()) - 20 * (entity.instance["speed"].getFloat())));
                            break;
                        case Communication::EventInput::Key_right:
                            Parser::setValue(entity.instance, std::string("x"), (float)((entity.instance["x"].getFloat()) + 20 * (entity.instance["speed"].getFloat())));
                            break;
                        default:
                            break;
                    }
                }
                server->removeInputAt(index);
            }
        }
        index++;
    }
}

void Game::updateColisions(std::shared_ptr<Server> server, Parser::entity_t &entity)
{
    if (entity.type != "__tile__") {
        for (auto &entity_colision : _entities) {
            if (entity_colision.type == "__tile__") {
                // HANDLE COLLISION
                if (checkColision(entity, entity_colision)) {
                    if ((entity.instance["hp"].getInt()) != 0) {
                        entity.instance["hp"] = 0;
                    }
                }
            }
            else if (entity_colision.type == "missile" && entity.type != "missile") {
                if ((entity.id) != (entity_colision.id)) {
                    if (checkColision(entity, entity_colision)) {
                        if (Parser::keyExists(entity.instance, "hp") && (entity.instance["hp"].getInt()) != 0) {
                            Parser::setValue(entity.instance, "hp", 0);
                        }
                    }
                }
            }
            else if (entity_colision.type == "bonus" && entity.type == "__player__") {
                if ((entity.id) != (entity_colision.id)) {
                    std::cout << entity_colision.instance["x"].getFloat() << " " << entity_colision.instance["y"].getFloat() << std::endl;
                    if (checkColision(entity, entity_colision)) {
                        std::cout << "COLISION" << std::endl;
                        if (entity_colision.instance["b_type"].getString().find("heal")) {
                            int hp = 0;
                            try {
                                hp = std::stoi(entity_colision.instance["b_type"].getString().substr(4, 6));
                            }
                            catch (std::exception &e) {
                                std::cout << "Bad bonus instance b_type " << e.what() << std::endl;
                            }
                            int new_hp = entity.instance["hp"].getInt() + hp > entity.instance["max_hp"].getInt() ?: entity.instance["max_hp"].getInt();
                            Parser::setValue(entity.instance, std::string("hp"), new_hp);
                        }
                        else if (entity_colision.instance["b_type"].getString().find("max_hp")) {
                            Parser::setValue(entity.instance, std::string("max_hp"), 200);
                        }
                        else if (entity_colision.instance["b_type"].getString().find("gun")) {
                            int gun = 0;
                            try {
                                gun = std::stoi(entity_colision.instance["b_type"].getString().substr(3, 4));
                            }
                            catch (std::exception &e) {
                                std::cout << "Bad bonus instance b_type " << e.what() << std::endl;
                            }
                            Parser::setValue(entity.instance, std::string("gun"), gun);
                        }
                        for (int i = 0; auto &entity : _entities) {
                            if (entity.id == entity_colision.id) {
                                _entities.erase(_entities.begin() + i);
                            }
                            i++;
                        }
                    }
                }
            }
        }
    }
}

void Game::updateEntities(std::shared_ptr<Server> server, Parser::entity_t &entity)
{
    if (entity.type == "missile") {
        std::cout << "MISSILE" << std::endl;
        // TODO: check if entity.instance["x"].getFloat() return infinity, if yes, throw exception
        // same for int

        Parser::setValue(entity.instance, "x", (entity.instance["x"].getFloat()) + (entity.instance["direction_x"].getFloat()) * (entity.instance["speed"].getFloat()));
        Parser::setValue(entity.instance, "y", (entity.instance["y"].getFloat()) + (entity.instance["direction_y"].getFloat()) * (entity.instance["speed"].getFloat()));
    }
    if (entity.type != "__player__" || entity.type != "missile") {
        std::cout << "UPDATE1" << std::endl;
        if (entity.type.substr(0, 4) != "boss" && Parser::keyExists(entity.instance, "x") && Parser::keyExists(entity.instance, "speed")) {
            Parser::setValue(entity.instance, "x", (entity.instance["x"].getFloat() - 1.0 * (entity.instance["speed"].getFloat() / 10.0)));
        }
        if (entity.type == "enemy2" || entity.type == "boss1") {
            if (Parser::keyExists(entity.instance, "y_status"))
                Parser::setValue(entity.instance, "y_status", 0);
            if (entity.instance["y_status"].getInt() == 0) {
                Parser::setValue(entity.instance, "y", entity.instance["y"].getFloat() + 1.0 * (entity.instance["speed"].getFloat() / 10.0));
                if (Parser::keyExists(entity.instance, "y") && entity.instance["y"].getFloat() <= 100.0)
                    Parser::setValue(entity.instance, "y_status", 1);
            }
            else {
                Parser::setValue(entity.instance, "y", entity.instance["y"].getFloat() - 1.0);
                if (Parser::keyExists(entity.instance, "y") && entity.instance["y"].getFloat() >= 900.0)
                    Parser::setValue(entity.instance, "y_status", 0);
            }
        }
    }
    if (entity.type == "__player__") {
        std::cout << "UPDATE2" << std::endl;
        if (Parser::keyExists(entity.instance, "x") && Parser::keyExists(entity.instance, "y") &&
            entity.id != 0 && server->getIds()[entity.id] == true)
            _ships.push_back(std::make_shared<Ship>(Communication::Position{(entity.instance["x"].getFloat()), (entity.instance["y"].getFloat())}, entity.id, ShipType::PLAYER));
    }
    else if (entity.type == "missile") {
        std::cout << "UPDATE3" << std::endl;
        std::cout << "Missile" << std::endl;
        if (Parser::keyExists(entity.instance, "x") || Parser::keyExists(entity.instance, "y") && Parser::keyExists(entity.instance, "direction_x") || Parser::keyExists(entity.instance, "direction_y") && Parser::keyExists(entity.instance, "speed"))
            return;
        _bullets.push_back(std::make_shared<Bullet>(Communication::Position{(entity.instance["x"].getFloat()), (entity.instance["y"].getFloat())}, Communication::Position{(entity.instance["direction_x"].getFloat()), (entity.instance["direction_y"].getFloat())}, (entity.instance["speed"].getFloat()), 1, 1));
    }
    else if (entity.type == "enemy_1" || entity.type == "enemy_2" || entity.type == "boss_1") {
        std::cout << "UPDATE4" << std::endl;
        if (Parser::keyExists(entity.instance, "x") || Parser::keyExists(entity.instance, "y"))
            return;
        _ships.push_back(std::make_shared<Ship>(Communication::Position{(entity.instance["x"].getFloat()), (entity.instance["y"].getFloat())}, entity.id, ShipType::ENEMY));
    }
    if (_loop % 5 == 0 && entity.type == "__player__") {
        std::cout << "UPDATE5" << std::endl;
        //_bullets[_bullets.size()] = std::make_shared<Bullet>(Communication::Position{(entity.instance["x"].getFloat()), (entity.instance["y"].getFloat())}, Communication::Position{(1), (0)}, (entity.instance["speed"].getFloat()), 1, 1);
    }
}

bool Game::checkColision(Parser::entity_t entity1, Parser::entity_t entity2)
{
    std::pair<float, float> scales = {1.0, 1.0};
    if (Parser::keyExists(entity1.instance, "scale"))
        scales.first = entity1.instance["scale"].getFloat();
    if (Parser::keyExists(entity2.instance, "scale"))
        scales.second = entity1.instance["scale"].getFloat();
    if (Parser::keyExists(entity1.instance, "x") && Parser::keyExists(entity1.instance, "y") && Parser::keyExists(entity2.instance, "x") && Parser::keyExists(entity2.instance, "y")) {
        if ((entity1.instance["x"].getFloat() + _tile_size * scales.first) >= entity2.instance["x"].getFloat() && entity1.instance["x"].getFloat() <= (entity2.instance["x"].getFloat() + _tile_size * scales.second) && (entity1.instance["y"].getFloat() + _tile_size * scales.first) >= entity2.instance["y"].getFloat() && entity1.instance["y"].getFloat() <= (entity2.instance["y"].getFloat() + _tile_size * scales.second))
            return true;
    }
    return false;
}

void Game::endGame()
{
}

void Game::sendShips(std::shared_ptr<Server> server)
{
    Communication::ShipsPosition shipsPosition;

    shipsPosition.nbrItems = 0;
    for (int i = 0; _ships.size() > i; i++) {
        shipsPosition.ship[shipsPosition.nbrItems].id = _ships[i]->getId();
        shipsPosition.ship[shipsPosition.nbrItems].life = _ships[i]->getLife();
        shipsPosition.ship[shipsPosition.nbrItems].level = _ships[i]->getLevel();
        shipsPosition.ship[shipsPosition.nbrItems].position.x = _ships[i]->getPos().x;
        shipsPosition.ship[shipsPosition.nbrItems].position.y = _ships[i]->getPos().y;
        shipsPosition.ship[shipsPosition.nbrItems].type = _ships[i]->getType();
        shipsPosition.nbrItems++;
        if (shipsPosition.nbrItems == 32) {
            server->sendToAll(shipsPosition);
            shipsPosition.nbrItems = 0;
            memset(&shipsPosition.ship, 0, sizeof(shipsPosition.ship));
        }
    }
    if (shipsPosition.nbrItems > 0) {
        server->sendToAll(shipsPosition);
    }
}

void Game::sendBullets(std::shared_ptr<Server> server)
{
    Communication::MissilesPosition missilesPosition;

    missilesPosition.nbrItems = 0;
    for (int i = 0; _bullets.size() > i; i++) {
        missilesPosition.missile[missilesPosition.nbrItems].id = _bullets[i]->getId();
        missilesPosition.missile[missilesPosition.nbrItems].position.x = _bullets[i]->getPos().x;
        missilesPosition.missile[missilesPosition.nbrItems].position.y = _bullets[i]->getPos().y;
        missilesPosition.missile[missilesPosition.nbrItems].direction.x = _bullets[i]->getDirection().x;
        missilesPosition.missile[missilesPosition.nbrItems].direction.y = _bullets[i]->getDirection().y;
        missilesPosition.missile[missilesPosition.nbrItems].speed = _bullets[i]->getSpeed();
        missilesPosition.missile[missilesPosition.nbrItems].damage = _bullets[i]->getDamage();
        missilesPosition.missile[missilesPosition.nbrItems].team_id = _bullets[i]->getTeam();
        missilesPosition.nbrItems++;
        if (missilesPosition.nbrItems == 32) {
            server->sendToAll(missilesPosition);
            missilesPosition.nbrItems = 0;
            memset(&missilesPosition.missile, 0, sizeof(missilesPosition.missile));
        }
    }
    if (missilesPosition.nbrItems > 0) {
        server->sendToAll(missilesPosition);
    }
}

void Game::sendBonus(std::shared_ptr<Server> server)
{
    Communication::BonusPosition bonusPosition;

    bonusPosition.nbrItems = 0;
    for (int i = 0; _bonus.size() > i; i++) {
        bonusPosition.bonus[bonusPosition.nbrItems].id = _bonus[i]->getId();
        bonusPosition.bonus[bonusPosition.nbrItems].position.x = _bonus[i]->getPos().x;
        bonusPosition.bonus[bonusPosition.nbrItems].position.y = _bonus[i]->getPos().y;
        bonusPosition.nbrItems++;
        if (bonusPosition.nbrItems == 32) {
            server->sendToAll(bonusPosition);
            bonusPosition.nbrItems = 0;
            memset(&bonusPosition.bonus, 0, sizeof(bonusPosition.bonus));
        }
    }
    if (bonusPosition.nbrItems > 0) {
        server->sendToAll(bonusPosition);
    }
}