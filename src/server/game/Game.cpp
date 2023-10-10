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
    updateGame(server);
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
    Parser::ParserJson parser = Parser::ParserJson(map_path);
    parser.parse();
    if (parser.getEntities().size() == 0)
        throw std::runtime_error("Error: no entities in map");
    _entities = parser.getEntities();
    for (auto &entity : _entities) {
        std::cout << "Entity: " << entity.type << std::endl;
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
    // sendBullets(server);
}

void Game::updateShips(std::shared_ptr<Server> server, Parser::entity_t entity)
{
    int index = 0;
    for (auto &communication : server->getInput()) {
        for (int i = 0; i < communication.second.nbrItems; i++) {
            if (entity.type == "player" && std::any_cast<int>(entity.instance["id"]) == communication.first) {
                if (entity.instance.find("speed") == entity.instance.end())
                    entity.instance["speed"] = 1;
                for (int i = 0; i < communication.second.nbrItems; i++) {
                    switch (communication.second.event[i]) {
                        case Communication::EventInput::Key_up:
                            entity.instance["y"] = std::any_cast<float>(entity.instance["y"]) - 1 * std::any_cast<float>(entity.instance["speed"]);
                            break;
                        case Communication::EventInput::Key_down:
                            entity.instance["y"] = std::any_cast<float>(entity.instance["y"]) + 1 * std::any_cast<float>(entity.instance["speed"]);
                            break;
                        case Communication::EventInput::Key_left:
                            entity.instance["x"] = std::any_cast<float>(entity.instance["x"]) - 1 * std::any_cast<float>(entity.instance["speed"]);
                            break;
                        case Communication::EventInput::Key_right:
                            entity.instance["x"] = std::any_cast<float>(entity.instance["x"]) + 1 * std::any_cast<float>(entity.instance["speed"]);
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
                if (std::any_cast<float>(entity.instance["x"]) == std::any_cast<float>(entity_colision.instance["x"]) && std::any_cast<float>(entity.instance["y"]) == std::any_cast<float>(entity_colision.instance["y"])) {
                    std::cout << "COLISION" << std::endl;
                    if (std::any_cast<int>(entity.instance["hp"]) != 0) {
                        entity.instance["hp"] = 0;
                    }
                }
            }
            else if (entity_colision.type == "missile" && entity.type != "missile") {
                if (std::any_cast<int>(entity.instance["id"]) != std::any_cast<int>(entity_colision.instance["id"])) {
                    if (std::any_cast<float>(entity.instance["x"]) == std::any_cast<float>(entity_colision.instance["x"]) && std::any_cast<float>(entity.instance["y"]) == std::any_cast<float>(entity_colision.instance["y"])) {
                        std::cout << "COLISION" << std::endl;
                        if (std::any_cast<int>(entity.instance["hp"]) != 0) {
                            entity.instance["hp"] = 0;
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
        entity.instance["x"] = std::any_cast<float>(entity.instance["x"]) + std::any_cast<float>(entity.instance["direction_x"]) * std::any_cast<float>(entity.instance["speed"]);
        entity.instance["y"] = std::any_cast<float>(entity.instance["y"]) + std::any_cast<float>(entity.instance["direction_y"]) * std::any_cast<float>(entity.instance["speed"]);
    }
    if (entity.type != "player" || entity.type != "missile") {
        entity.instance["x"] = std::any_cast<float>(entity.instance["x"]) - 1;
    }
    if (entity.type == "player") {
        _ships.push_back(std::make_shared<Ship>(Communication::Position{std::any_cast<float>(entity.instance["x"]), std::any_cast<float>(entity.instance["y"])}, std::any_cast<int>(entity.instance["id"]), ShipType::PLAYER));

        _entities.push_back(static_cast<Parser::entity_t>(
            Parser::entity_t({"missile",
                              {std::vector<std::string>({})},
                              std::map<std::string, std::any>{
                                  {"x", std::any_cast<float>(entity.instance["x"]) + 1},
                                  {"y", std::any_cast<float>(entity.instance["y"])},
                                  {"speed", 2},
                                  {"id", std::any_cast<int>(entity.instance["id"])},
                                  {"direction_x", 1.0},
                                  {"direction_y", 0.0}},
                              std::map<std::string, Parser::type_t>{
                                  {"x", Parser::type_t::INT},
                                  {"y", Parser::type_t::INT},
                                  {"speed", Parser::type_t::FLOAT},
                                  {"id", Parser::type_t::INT},
                                  {"direction_x", Parser::type_t::FLOAT},
                                  {"direction_y", Parser::type_t::FLOAT}}})));
    }
    else if (entity.type == "missile") {
        _bullets.push_back(std::make_shared<Bullet>(Communication::Position{std::any_cast<float>(entity.instance["x"]), std::any_cast<float>(entity.instance["y"])}, Communication::Position{std::any_cast<float>(entity.instance["direction_x"]), std::any_cast<float>(entity.instance["direction_y"])}, std::any_cast<float>(entity.instance["speed"]), 1, 1));
    }
    else if (entity.type == "enemy") {
        _ships.push_back(std::make_shared<Ship>(Communication::Position{std::any_cast<float>(entity.instance["x"]), std::any_cast<float>(entity.instance["y"])}, std::any_cast<int>(entity.instance["id"]), ShipType::ENEMY));
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
