/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Game
*/

#include "Game.hpp"
#include "Communication.hpp"
#include "TransformPath.hpp"

Server::Game::Game()
    : _level(0), _score(0), _loop(0)
{
    _init = false;
}

Server::Game::~Game()
{
}

void Server::Game::run(std::shared_ptr<Server::UDPServer> server)
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
                        initGame(transformPath(std::string("levels/level_1.json")));
                    server->sendToAll(timer);
                }
            }
            if (!is_running(0))
                return;
            this->run(server);
        });
    server->getIoService().run();
}

void Server::Game::setLevel(int level)
{
    _level = level;
}

void Server::Game::setScore(int score)
{
    _score = score;
}

int Server::Game::getLevel() const
{
    return _level;
}

int Server::Game::getScore() const
{
    return _score;
}

void Server::Game::initGame(std::string map_path)
{
    _init = true;
    int _last_entity_id = 0;
    Parser::ParserJson parser = Parser::ParserJson(map_path).parse();
    for (Parser::entity_t entity : parser.getEntities()) {
        _entities.push_back(std::optional<Parser::entity_t>{entity});
    }
    _tile_size = parser.getTileSize();
    for (std::optional<Parser::entity_t> &entity : _entities) {
        if (entity.has_value()) {
            if (Parser::keyExists(entity.value().instance, "id") && (entity.value().id) > _last_entity_id) {
                _last_entity_id = entity.value().id;
            }
            if (entity.value().type == "__player__")
                Parser::setValue(entity.value().instance, "team", 0);
            if (entity.value().type == "enemy_1" || entity.value().type == "enemy_2" || entity.value().type == "boss_1") {
                Parser::setValue(entity.value().instance, "team", 1);
                if (!Parser::keyExists(entity.value().instance, "y_status"))
                    Parser::setValue(entity.value().instance, "y_status", 0);
            }
        }
    }
}

void Server::Game::updateGame(std::shared_ptr<Server::UDPServer> server)
{
    for (auto &entity : _entities) {
        if (!entity.has_value())
            continue;
        updateShips(server, entity);
        updateColisions(server, entity);
        updateEntities(server, entity);
    }
    sendShips(server);
    sendBullets(server);
    sendBonus(server);
    _ships.clear();
    _bullets.clear();
    _bonus.clear();
    _loop++;
}

void Server::Game::updateShips(std::shared_ptr<Server::UDPServer> server, std::optional<Parser::entity_t> &entity)
{
    int index = 0;
    if (!entity.has_value())
        return;
    for (auto &communication : server->getInput()) {
        for (int i = 0; i < communication.second.nbrItems; i++) {
            if (entity.value().type == "__player__" && entity.value().id == communication.first) {
                if (entity.value().instance.find("speed") == entity.value().instance.end()) {
                    Parser::setValue(entity.value().instance, "speed", 1.0);
                }
                int move[4] = {0, 0, 0, 0};
                for (int i = 0; i < communication.second.nbrItems; i++) {
                    switch (communication.second.event[i]) {
                        case Communication::EventInput::Key_up:
                            move[0] = 1;
                            break;
                        case Communication::EventInput::Key_down:
                            move[1] = 1;
                            break;
                        case Communication::EventInput::Key_left:
                            move[2] = 1;
                            break;
                        case Communication::EventInput::Key_right:
                            move[3] = 1;
                            break;
                        default:
                            break;
                    }
                }
                if (move[0] == 1 && move[1] == 1 && move[2] == 1 && move[3] == 1) {
                    server->removeInputAt(index);
                    continue;
                }
                if (move[0] == 1 && move[1] == 1) {
                    move[0] = 0;
                    move[1] = 0;
                }
                if (move[2] == 1 && move[3] == 1) {
                    move[2] = 0;
                    move[3] = 0;
                }
                if (move[1] == 1 && move[3] == 1) {
                    Parser::setValue(entity.value().instance, std::string("y"), (float)((entity.value().instance["y"].getFloat()) + 5.0 * (entity.value().instance["speed"].getFloat()) / 1.5));
                    if (entity.value().instance["y"].getFloat() > 980.0 - _tile_size * (entity.value().instance["scale"].getFloat()))
                        Parser::setValue(entity.value().instance, std::string("y"), 980.0 - _tile_size * (entity.value().instance["scale"].getFloat()));
                    Parser::setValue(entity.value().instance, std::string("x"), (float)((entity.value().instance["x"].getFloat()) + 5.0 * (entity.value().instance["speed"].getFloat()) / 1.5));
                    if (entity.value().instance["x"].getFloat() > 1920.0 - _tile_size * (entity.value().instance["scale"].getFloat()))
                        Parser::setValue(entity.value().instance, std::string("x"), 1920.0 - _tile_size * (entity.value().instance["scale"].getFloat()));
                    server->removeInputAt(index);
                    continue;
                }
                if (move[0] == 1 && move[3] == 1) {
                    Parser::setValue(entity.value().instance, std::string("y"), (float)((entity.value().instance["y"].getFloat()) - 5.0 * (entity.value().instance["speed"].getFloat()) / 1.5));
                    if (entity.value().instance["y"].getFloat() < 100.0)
                        Parser::setValue(entity.value().instance, std::string("y"), 100.0);
                    Parser::setValue(entity.value().instance, std::string("x"), (float)((entity.value().instance["x"].getFloat()) + 5.0 * (entity.value().instance["speed"].getFloat()) / 1.5));
                    if (entity.value().instance["x"].getFloat() > 1920.0 - _tile_size * (entity.value().instance["scale"].getFloat()))
                        Parser::setValue(entity.value().instance, std::string("x"), 1920.0 - _tile_size * (entity.value().instance["scale"].getFloat()));
                    server->removeInputAt(index);
                    continue;
                }
                if (move[0] == 1 && move[2] == 1) {
                    Parser::setValue(entity.value().instance, std::string("y"), (float)((entity.value().instance["y"].getFloat()) - 5.0 * (entity.value().instance["speed"].getFloat()) / 1.5));
                    if (entity.value().instance["y"].getFloat() < 100.0)
                        Parser::setValue(entity.value().instance, std::string("y"), 100.0);
                    Parser::setValue(entity.value().instance, std::string("x"), (float)((entity.value().instance["x"].getFloat()) - 5.0 * (entity.value().instance["speed"].getFloat()) / 1.5));
                    if (entity.value().instance["x"].getFloat() < 0.0)
                        Parser::setValue(entity.value().instance, std::string("x"), 0.0);
                    server->removeInputAt(index);
                    continue;
                }
                if (move[1] == 1 && move[2] == 1) {
                    Parser::setValue(entity.value().instance, std::string("y"), (float)((entity.value().instance["y"].getFloat()) + 5.0 * (entity.value().instance["speed"].getFloat()) / 1.5));
                    if (entity.value().instance["y"].getFloat() > 980 - _tile_size * (entity.value().instance["scale"].getFloat()))
                        Parser::setValue(entity.value().instance, std::string("y"), 980.0 - _tile_size * (entity.value().instance["scale"].getFloat()));
                    Parser::setValue(entity.value().instance, std::string("x"), (float)((entity.value().instance["x"].getFloat()) - 5.0 * (entity.value().instance["speed"].getFloat()) / 1.5));
                    if (entity.value().instance["x"].getFloat() < 0.0)
                        Parser::setValue(entity.value().instance, std::string("x"), 0.0);
                    server->removeInputAt(index);
                    continue;
                }
                if (move[0] == 1 && (move[2] == 0 || move[3] == 0)) {
                    Parser::setValue(entity.value().instance, std::string("y"), (float)((entity.value().instance["y"].getFloat()) - 5.0 * (entity.value().instance["speed"].getFloat())));
                    if (entity.value().instance["y"].getFloat() < 100.0)
                        Parser::setValue(entity.value().instance, std::string("y"), 100.0);
                }
                if (move[1] == 1 && (move[2] == 0 || move[3] == 0)) {
                    Parser::setValue(entity.value().instance, std::string("y"), (float)((entity.value().instance["y"].getFloat()) + 5.0 * (entity.value().instance["speed"].getFloat())));
                    if (entity.value().instance["y"].getFloat() > 980.0 - _tile_size * (entity.value().instance["scale"].getFloat()))
                        Parser::setValue(entity.value().instance, std::string("y"), 980.0 - _tile_size * (entity.value().instance["scale"].getFloat()));
                }
                if (move[2] == 1 && (move[0] == 0 || move[1] == 0)) {
                    Parser::setValue(entity.value().instance, std::string("x"), (float)((entity.value().instance["x"].getFloat()) - 5.0 * (entity.value().instance["speed"].getFloat())));
                    if (entity.value().instance["x"].getFloat() < 0.0)
                        Parser::setValue(entity.value().instance, std::string("x"), 0.0);
                }
                if (move[3] == 1 && (move[0] == 0 || move[1] == 0)) {
                    Parser::setValue(entity.value().instance, std::string("x"), (float)((entity.value().instance["x"].getFloat()) + 5.0 * (entity.value().instance["speed"].getFloat())));
                    if (entity.value().instance["x"].getFloat() > 1920.0 - _tile_size * (entity.value().instance["scale"].getFloat()))
                        Parser::setValue(entity.value().instance, std::string("x"), 1920.0 - _tile_size * (entity.value().instance["scale"].getFloat()));
                }
                server->removeInputAt(index);
            }
        }
        index++;
    }
}

void Server::Game::updateColisions(std::shared_ptr<Server::UDPServer> server, std::optional<Parser::entity_t> &entity)
{
    if (!entity.has_value())
        return;
    if (entity.value().type != "__tile__") {
        for (auto &entity_colision : _entities) {
            if (!entity_colision.has_value())
                continue;
            // if (entity_colision.value().type == "__tile__") {
            //     // HANDLE COLLISION
            //     if (checkColision(entity.value(), entity_colision)) {
            //         if ((entity.value().instance["hp"].getInt()) != 0) {
            //             entity.value().instance["hp"] = 0;
            //         }
            //     }
            // }
            if (entity_colision.has_value() && entity_colision.value().type == "missile" && Parser::keyExists(entity_colision.value().instance, "team")) {
                if (entity.has_value() && entity_colision.has_value() && (entity.value().id) != (entity_colision.value().id) && entity.value().instance["team"].getInt() != entity_colision.value().instance["team"].getInt()) {
                    if (checkColision(entity.value(), entity_colision.value())) {
                        int damage = entity_colision.value().instance["damage"].getFloat();
                        if (Parser::keyExists(entity.value().instance, "hp") && (entity.value().instance["hp"].getInt()) != 0) {
                            if (entity.value().type == "__player__") {
                                Parser::setValue(entity.value().instance, "hp", entity.value().instance["hp"].getInt() - 10.0);
                            }
                            Parser::setValue(entity.value().instance, "hp", entity.value().instance["hp"].getInt() - damage);
                        }
                        else {
                            if (entity.value().type == "enemy_1" || entity.value().type == "enemy_2") {
                                // Random 1/3
                                if (rand() % 3 == 0) {
                                    Parser::entity_t newEntity;
                                    newEntity.id = _entities.size();
                                    newEntity.type = "bonus";
                                    newEntity.textures = (std::pair<std::vector<std::string>, std::vector<int>>){};
                                    newEntity.instance = {};
                                    Parser::setValue(newEntity.instance, "x", (entity.value().instance["x"].getFloat()));
                                    Parser::setValue(newEntity.instance, "y", (entity.value().instance["y"].getFloat()));
                                    int b_type = rand() % 6;
                                    switch (b_type) {
                                        case 0:
                                            Parser::setValue(newEntity.instance, "b_type", std::string("heal30"));
                                            break;
                                        case 1:
                                            Parser::setValue(newEntity.instance, "b_type", std::string("heal50"));
                                            break;
                                        case 2:
                                            Parser::setValue(newEntity.instance, "b_type", std::string("heal100"));
                                            break;
                                        case 3:
                                            Parser::setValue(newEntity.instance, "b_type", std::string("max_hp"));
                                            break;
                                        case 4:
                                            Parser::setValue(newEntity.instance, "b_type", std::string("gun1"));
                                            break;
                                        case 5:
                                            Parser::setValue(newEntity.instance, "b_type", std::string("gun2"));
                                            break;
                                        case 6:
                                            Parser::setValue(newEntity.instance, "b_type", std::string("gun3"));
                                            break;
                                    }
                                    _entities.push_back(std::optional<Parser::entity_t>{newEntity});
                                }
                            }
                            else if (entity.value().type == "boss_1") {
                                server->sendToAll("quit");
                                endGame();
                            }
                            else {
                                sendDelete(server, entity.value().id);
                                entity = std::nullopt;
                            }
                        }
                        sendDelete(server, entity_colision.value().id);
                        entity_colision = std::nullopt;
                        return;
                    }
                }
            }
            else if (entity_colision.value().type == "bonus" && entity.value().type == "__player__") {
                if ((entity.value().id) != (entity_colision.value().id)) {
                    if (checkColision(entity.value(), entity_colision.value())) {
                        if (entity_colision.value().instance["b_type"].getString().find("heal") != std::string::npos) {
                            int hp = 0;
                            try {
                                hp = std::stoi(entity_colision.value().instance["b_type"].getString().substr(4, 6));
                            }
                            catch (std::exception &e) {
                                std::cerr << "Bad bonus instance b_type " << e.what() << std::endl;
                            }
                            if (!Parser::keyExists(entity.value().instance, "max_hp"))
                                Parser::setValue(entity.value().instance, std::string("max_hp"), 100);
                            if (Parser::keyExists(entity.value().instance, "hp") && entity.value().instance["hp"].getInt() + hp <= entity.value().instance["max_hp"].getInt()) {
                                Parser::setValue(entity.value().instance, std::string("hp"), entity.value().instance["hp"].getInt() + hp);
                            }
                            else {
                                Parser::setValue(entity.value().instance, std::string("hp"), entity.value().instance["max_hp"].getInt());
                            }
                        }
                        else if (entity_colision.value().instance["b_type"].getString().find("max_hp") != std::string::npos) {
                            Parser::setValue(entity.value().instance, std::string("max_hp"), 200);
                        }
                        else if (entity_colision.value().instance["b_type"].getString().find("gun") != std::string::npos) {
                            int gun = 0;
                            try {
                                gun = std::stoi(entity_colision.value().instance["b_type"].getString().substr(3, 4));
                            }
                            catch (std::exception &e) {
                                std::cerr << "Bad bonus instance b_type " << e.what() << std::endl;
                            }
                            Parser::setValue(entity.value().instance, std::string("gun"), gun);
                        }
                        sendDelete(server, entity_colision.value().id);
                        entity_colision = std::nullopt;
                        return;
                    }
                }
            }
        }
    }
}

void Server::Game::updateEntities(std::shared_ptr<Server::UDPServer> server, std::optional<Parser::entity_t> &entity)
{
    if (!entity.has_value())
        return;
    if (entity.value().type == "missile") {
        if (Parser::keyExists(entity.value().instance, "x") && Parser::keyExists(entity.value().instance, "y") && Parser::keyExists(entity.value().instance, "direction_x") && Parser::keyExists(entity.value().instance, "direction_y") && Parser::keyExists(entity.value().instance, "speed")) {
            Parser::setValue(entity.value().instance, "x", (entity.value().instance["x"].getFloat()) + (entity.value().instance["direction_x"].getFloat()) * (entity.value().instance["speed"].getFloat()));
            Parser::setValue(entity.value().instance, "y", (entity.value().instance["y"].getFloat()) + (entity.value().instance["direction_y"].getFloat()) * (entity.value().instance["speed"].getFloat()));
        }
    }
    if (entity.value().type != "__player__" && entity.value().type != "missile") {
        if (Parser::keyExists(entity.value().instance, "x") && Parser::keyExists(entity.value().instance, "speed")) {
            if (entity.value().type.substr(0, 4) == "boss" && entity.value().instance["x"].getFloat() >= 1800.0) {
                Parser::setValue(entity.value().instance, "x", (entity.value().instance["x"].getFloat() - 5.0 * (entity.value().instance["speed"].getFloat())));
            }
            else if (entity.value().type.substr(0, 4) != "boss") {
                Parser::setValue(entity.value().instance, "x", (entity.value().instance["x"].getFloat() - 5.0 * (entity.value().instance["speed"].getFloat())));
            }
        }
        if (entity.value().type == "enemy_2" || entity.value().type == "boss_1") {
            if (entity.value().instance["y_status"].getInt() == 0) {
                Parser::setValue(entity.value().instance, "y", entity.value().instance["y"].getFloat() + 5.0 * (entity.value().instance["speed"].getFloat()));
                if (Parser::keyExists(entity.value().instance, "y") && entity.value().instance["y"].getFloat() >= 1020.0)
                    Parser::setValue(entity.value().instance, "y_status", 1);
            }
            else {
                Parser::setValue(entity.value().instance, "y", entity.value().instance["y"].getFloat() - 5.0 * (entity.value().instance["speed"].getFloat()));
                if (Parser::keyExists(entity.value().instance, "y") && entity.value().instance["y"].getFloat() <= 100.0)
                    Parser::setValue(entity.value().instance, "y_status", 0);
            }
        }
        else if (entity.value().type == "__tile__") {
            if (Parser::keyExists(entity.value().instance, "x") && entity.value().instance["x"].getFloat() <= -_tile_size) {
                entity = std::nullopt;
                return;
            }
            else {
                Parser::setValue(entity.value().instance, "x", (entity.value().instance["x"].getFloat() - 5.0));
            }
        }
    }
    if (entity.value().type == "__player__") {
        if (Parser::keyExists(entity.value().instance, "x") &&
            Parser::keyExists(entity.value().instance, "y") &&
            Parser::keyExists(entity.value().instance, "scale") &&
            entity.value().id != 0 &&
            server->getIds()[entity.value().id] == true) {
            _ships.push_back(std::make_shared<Ship>(Communication::Position{(entity.value().instance["x"].getFloat()), (entity.value().instance["y"].getFloat())}, entity.value().id, getShipType(entity.value().type), entity.value().instance["scale"].getFloat()));
            if (_loop % 25 == 0) {
                Parser::entity_t newEntity;
                newEntity.id = _entities.size();
                newEntity.type = "missile";
                newEntity.textures = (std::pair<std::vector<std::string>, std::vector<int>>){};
                newEntity.instance = {};
                Parser::setValue(newEntity.instance, "x", (entity.value().instance["x"].getFloat() + (_tile_size / 1.5) * (entity.value().instance["scale"].getFloat())));
                Parser::setValue(newEntity.instance, "y", (entity.value().instance["y"].getFloat() + (_tile_size / 2) * (entity.value().instance["scale"].getFloat())));
                Parser::setValue(newEntity.instance, "direction_x", (1.0));
                Parser::setValue(newEntity.instance, "direction_y", (0.0));
                Parser::setValue(newEntity.instance, "speed", (15.0));
                if (!Parser::keyExists(entity.value().instance, "gun"))
                    Parser::setValue(entity.value().instance, "gun", 1);
                Parser::setValue(newEntity.instance, "damage", (10.0) * (entity.value().instance["gun"].getInt()));
                Parser::setValue(newEntity.instance, "team", 0);
                Parser::setValue(newEntity.instance, "scale", 0.1);
                _entities.push_back(std::optional<Parser::entity_t>{newEntity});
                _bullets.push_back(std::make_shared<Bullet>(
                    Communication::Position{(newEntity.instance["x"].getFloat()),
                                            (newEntity.instance["y"].getFloat())},
                    Communication::Position{(newEntity.instance["direction_x"].getFloat()),
                                            (newEntity.instance["direction_y"].getFloat())},
                    newEntity.instance["speed"].getFloat(),
                    newEntity.instance["damage"].getFloat(), newEntity.id));
            }
        }
    }
    else if (entity.value().type == "missile") {
        if (Parser::keyExists(entity.value().instance, "x") && Parser::keyExists(entity.value().instance, "y") && Parser::keyExists(entity.value().instance, "direction_x") && Parser::keyExists(entity.value().instance, "direction_y") && Parser::keyExists(entity.value().instance, "speed") && entity.value().id != 0) {
            if (entity.value().instance["x"].getFloat() < -100.0 || entity.value().instance["x"].getFloat() > 2120.0 || entity.value().instance["y"].getFloat() < 0.0 || entity.value().instance["y"].getFloat() > 1080.0) {
                sendDelete(server, entity.value().id);
                entity = std::nullopt;
                return;
            }
            else {
                _bullets.push_back(std::make_shared<Bullet>(Communication::Position{(entity.value().instance["x"].getFloat() + ((entity.value().instance["speed"].getFloat()) * entity.value().instance["direction_x"].getFloat())), (entity.value().instance["y"].getFloat() - ((entity.value().instance["speed"].getFloat()) * entity.value().instance["direction_y"].getFloat()))}, Communication::Position{(entity.value().instance["direction_x"].getFloat()), (entity.value().instance["direction_y"].getFloat())}, (entity.value().instance["speed"].getFloat()), 1, entity.value().id));
            }
        }
    }
    else if (entity.value().type == "enemy_1" || entity.value().type == "enemy_2" || entity.value().type == "boss_1") {
        if (!Parser::keyExists(entity.value().instance, "x") || !Parser::keyExists(entity.value().instance, "y") || !Parser::keyExists(entity.value().instance, "scale"))
            return;
        if (entity.value().instance["x"].getFloat() < -100.0 || entity.value().instance["hp"].getFloat() <= 0.0) {
            sendDelete(server, entity.value().id);
            entity = std::nullopt;
            return;
        }
        _ships.push_back(std::make_shared<Ship>(Communication::Position{(entity.value().instance["x"].getFloat()), (entity.value().instance["y"].getFloat())}, entity.value().id, getShipType(entity.value().type), entity.value().instance["scale"].getFloat()));
        if (_loop % 50 == 0 && entity.value().instance["x"].getFloat() <= 1920.0) {
            Parser::entity_t newEntity;
            newEntity.id = _entities.size();
            newEntity.type = "missile";
            newEntity.textures = (std::pair<std::vector<std::string>, std::vector<int>>){};
            newEntity.instance = {};
            Parser::setValue(newEntity.instance, "x", (entity.value().instance["x"].getFloat() - (_tile_size / 1.5) * (entity.value().instance["scale"].getFloat())));
            Parser::setValue(newEntity.instance, "y", (entity.value().instance["y"].getFloat() + (_tile_size / 2) * (entity.value().instance["scale"].getFloat())));
            Parser::setValue(newEntity.instance, "direction_x", (-1.0));
            Parser::setValue(newEntity.instance, "direction_y", (0.0));
            Parser::setValue(newEntity.instance, "speed", (15.0));
            Parser::setValue(newEntity.instance, "damage", 10.0);
            Parser::setValue(newEntity.instance, "team", 1);
            Parser::setValue(newEntity.instance, "scale", 0.1);
            _entities.push_back(std::optional<Parser::entity_t>{newEntity});
            _bullets.push_back(std::make_shared<Bullet>(Communication::Position{(newEntity.instance["x"].getFloat()), (newEntity.instance["y"].getFloat())}, Communication::Position{(newEntity.instance["direction_x"].getFloat()), (newEntity.instance["direction_y"].getFloat())}, newEntity.instance["speed"].getFloat(), newEntity.instance["damage"].getFloat(), newEntity.id));
        }
    }
    if (entity.has_value() && entity.value().type == "bonus" && Parser::keyExists(entity.value().instance, "x") && Parser::keyExists(entity.value().instance, "y") && Parser::keyExists(entity.value().instance, "b_type"))
        _bonus.push_back(std::make_shared<Bonus>(Communication::Position{(entity.value().instance["x"].getFloat()), (entity.value().instance["y"].getFloat())}, entity.value().id, getBonusType(entity.value().instance["b_type"].getString())));
}

bool Server::Game::checkColision(std::optional<Parser::entity_t> entity1, std::optional<Parser::entity_t> entity2)
{
    if (!entity1.has_value() || !entity2.has_value())
        return false;
    std::pair<float, float> scales = {1.0, 1.0};
    if (Parser::keyExists(entity1.value().instance, "scale"))
        scales.first = entity1.value().instance["scale"].getFloat();
    if (Parser::keyExists(entity2.value().instance, "scale"))
        scales.second = entity2.value().instance["scale"].getFloat();
    if (Parser::keyExists(entity1.value().instance, "x") && Parser::keyExists(entity1.value().instance, "y") && Parser::keyExists(entity2.value().instance, "x") && Parser::keyExists(entity2.value().instance, "y")) {
        if ((entity1.value().instance["x"].getFloat() + _tile_size * scales.first) >= entity2.value().instance["x"].getFloat() &&
            entity1.value().instance["x"].getFloat() <= (entity2.value().instance["x"].getFloat() + _tile_size * scales.second) &&
            (entity1.value().instance["y"].getFloat() + _tile_size * scales.first) >= entity2.value().instance["y"].getFloat() &&
            entity1.value().instance["y"].getFloat() <= (entity2.value().instance["y"].getFloat() + _tile_size * scales.second)) {
            return true;
        }
    }
    return false;
}

void Server::Game::endGame()
{
}

void Server::Game::sendShips(std::shared_ptr<Server::UDPServer> server)
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
        shipsPosition.ship[shipsPosition.nbrItems].scale = _ships[i]->getScale();
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

void Server::Game::sendBullets(std::shared_ptr<Server::UDPServer> server)
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

void Server::Game::sendBonus(std::shared_ptr<Server::UDPServer> server)
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

void Server::Game::sendDelete(std::shared_ptr<Server::UDPServer> server, int id)
{
    Communication::Delete idToDelete;

    idToDelete.id = id;
    server->sendToAll(idToDelete);
}

ShipType Server::Game::getShipType(std::string type)
{
    if (type == "enemy_1")
        return ShipType::ENEMY1;
    if (type == "enemy_2")
        return ShipType::ENEMY2;
    if (type == "boss_1")
        return ShipType::BOSS1;
    return ShipType::PLAYER;
}

BonusType Server::Game::getBonusType(std::string type)
{
    if (type == "heal30")
        return BonusType::HEAL30;
    if (type == "heal50")
        return BonusType::HEAL50;
    if (type == "heal100")
        return BonusType::HEAL100;
    if (type == "max_hp")
        return BonusType::MAX_HP;
    if (type == "gun1")
        return BonusType::GUN1;
    if (type == "gun2")
        return BonusType::GUN2;
    if (type == "gun3")
        return BonusType::GUN3;
    return BonusType::UNKNOW;
}