/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Game
*/

#include "Game.hpp"
#include "Communication.hpp"

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
                        initGame("assets/map.json");
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
    if (parser.getEntities().size() == 0)
        _entities = parser.getEntities();
    for (auto &entity : _entities) {
        if (entity.instance.find("id") != entity.instance.end() && (entity.instance["id"].getInt()) > _last_entity_id) {
            _last_entity_id = entity.instance["id"].getInt();
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
    sendShips(server);
    _bullets.clear();
    _ships.clear();
    // sendBullets(server);
}

void Game::updateShips(std::shared_ptr<Server> server, Parser::entity_t entity)
{
    int index = 0;
    for (auto &communication : server->getInput()) {
        for (int i = 0; i < communication.second.nbrItems; i++) {
            if (entity.type == "player" && (entity.instance["id"].getInt()) == communication.first) {
                if (entity.instance.find("speed") == entity.instance.end()) {
                    entity.instance.insert({"speed", Parser::Any(1)});
                }
                for (int i = 0; i < communication.second.nbrItems; i++) {
                    switch (communication.second.event[i]) {
                        case Communication::EventInput::Key_up:
                            entity.instance.insert({"y", Parser::Any((entity.instance["y"].getFloat()) - 1 * (entity.instance["speed"].getFloat()))});
                            break;
                        case Communication::EventInput::Key_down:
                            entity.instance.insert({"y", Parser::Any((entity.instance["y"].getFloat()) + 1 * (entity.instance["speed"].getFloat()))});
                            break;
                        case Communication::EventInput::Key_left:
                            entity.instance.insert({"x", Parser::Any((entity.instance["x"].getFloat()) - 1 * (entity.instance["speed"].getFloat()))});
                            break;
                        case Communication::EventInput::Key_right:
                            entity.instance.insert({"x", Parser::Any((entity.instance["x"].getFloat()) + 1 * (entity.instance["speed"].getFloat()))});
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

void Game::updateColisions(std::shared_ptr<Server> server, Parser::entity_t entity)
{
    if (entity.type != "__tile__") {
        for (auto &entity_colision : _entities) {
            if (entity_colision.type == "__tile__") {
                // HANDLE COLLISION
                if ((entity.instance["x"].getFloat()) == (entity_colision.instance["x"].getFloat()) && (entity.instance["y"].getFloat()) == (entity_colision.instance["y"].getFloat())) {
                    std::cout << "COLISION" << std::endl;
                    if ((entity.instance["hp"].getInt()) != 0) {
                        entity.instance["hp"] = 0;
                    }
                }
            }
            else if (entity_colision.type == "missile" && entity.type != "missile") {
                if ((entity.instance["id"].getInt()) != (entity_colision.instance["id"].getInt())) {
                    if ((entity.instance["x"].getFloat()) == (entity_colision.instance["x"].getFloat()) && (entity.instance["y"].getFloat()) == (entity_colision.instance["y"].getFloat())) {
                        std::cout << "COLISION" << std::endl;
                        if ((entity.instance["hp"].getInt()) != 0) {
                            entity.instance.insert({"hp", Parser::Any(0)});
                        }
                    }
                }
            }
        }
    }
}

void Game::updateEntities(std::shared_ptr<Server> server, Parser::entity_t entity)
{
    if (entity.type == "missile") {
        // TODO: check if entity.instance["x"].getFloat() return infinity, if yes, throw exception
        // same for int

        entity.instance.insert({"x", Parser::Any((entity.instance["x"].getFloat()) + (entity.instance["direction_x"].getFloat()) * (entity.instance["speed"].getFloat()))});
        entity.instance.insert({"y", Parser::Any((entity.instance["y"].getFloat()) + (entity.instance["direction_y"].getFloat()) * (entity.instance["speed"].getFloat()))});
    }
    if (entity.type != "__player__" || entity.type != "missile") {
        if (entity.type.substr(0, 4) != "boss")
            entity.instance.insert({"x", Parser::Any((entity.instance["x"].getFloat() - 1.0 * (entity.instance["speed"].getFloat() / 10.0)))});
        if (entity.type == "enemy2" || entity.type == "boss1") {
            if (entity.instance.find("y_status") == entity.instance.end())
                entity.instance.insert({"y_status", Parser::Any(0)});
            if (entity.instance["y_status"].getInt() == 0) {
                entity.instance.insert({"y", Parser::Any((entity.instance["y"].getFloat() + 1.0 * (entity.instance["speed"].getFloat() / 10.0)))});
                if (entity.instance.find("y") != entity.instance.end() && entity.instance["y"].getFloat() <= 100.0)
                    entity.instance.insert({"y_status", Parser::Any(1)});
            }
            else {
                entity.instance.insert({"y", Parser::Any((entity.instance["y"].getFloat() - 1.0))});
                if (entity.instance.find("y") != entity.instance.end() && entity.instance["y"].getFloat() >= 900.0)
                    entity.instance.insert({"y_status", Parser::Any(0)});
            }
        }
    }
    if (entity.type == "__player__") {
        if (entity.instance.find("x") != entity.instance.end() && entity.instance.find("y") != entity.instance.end() &&
            entity.id != 0 && server->getIds()[entity.id] == true)
            _ships.push_back(std::make_shared<Ship>(Communication::Position{(entity.instance["x"].getFloat()), (entity.instance["y"].getFloat())}, entity.id, ShipType::PLAYER));

        // std::cout << "Player2" << std::endl;
        // _entities.push_back(static_cast<Parser::entity_t>(
        //     Parser::entity_t({
        //         "missile",
        //         {{}, {}},
        //         std::unordered_map<std::string, Parser::Any>{
        //             {"x", Parser::Any((entity.instance["x"].getFloat()) + 1.0)},
        //             {"y", Parser::Any(entity.instance["y"].getFloat())},
        //             {"speed", Parser::Any(2.0)},
        //             {"id", Parser::Any(_last_entity_id++)},
        //             {"direction_x", Parser::Any(1.0)},
        //             {"direction_y", Parser::Any(0.0)}},
        //     })));
    }
    else if (entity.type == "missile") {
        std::cout << "Missile" << std::endl;
        if (entity.instance.find("x") == entity.instance.end() || entity.instance.find("y") == entity.instance.end() && entity.instance.find("direction_x") == entity.instance.end() || entity.instance.find("direction_y") == entity.instance.end() && entity.instance.find("speed") == entity.instance.end())
            return;
        _bullets.push_back(std::make_shared<Bullet>(Communication::Position{(entity.instance["x"].getFloat()), (entity.instance["y"].getFloat())}, Communication::Position{(entity.instance["direction_x"].getFloat()), (entity.instance["direction_y"].getFloat())}, (entity.instance["speed"].getFloat()), 1, 1));
    }
    else if (entity.type == "enemy_1" || entity.type == "enemy_2" || entity.type == "boss_1") {
        if (entity.instance.find("x") == entity.instance.end() || entity.instance.find("y") == entity.instance.end())
            return;
        _ships.push_back(std::make_shared<Ship>(Communication::Position{(entity.instance["x"].getFloat()), (entity.instance["y"].getFloat())}, entity.id, ShipType::ENEMY));
    }
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
