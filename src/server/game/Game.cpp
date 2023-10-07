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
    updateGame(server->getInput(), server);
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
                    std::cout << "Timer: " << timerCount << " " << timer.time << std::endl;
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

void Game::updateGame(std::vector<Communication::Input>, std::shared_ptr<Server> server)
{
    for (auto &entity : _entities) {
        if (entity.type != "player") {
            entity.instance["x"] = std::any_cast<int>(entity.instance["x"]) + 1;
            std::cout << "Entity: " << entity.type << " x: " << std::any_cast<int>(entity.instance["x"]) << std::endl;
        }
        for (auto &communication : communications) {
            if (std::any_cast<int>(entity.instance["id"]) == communication.first) {
                // HANDLE PLAYER POSITION OR ACTION
            }
        }
        if (entity.type != "__tile__") {
            for (auto &entity_colision : _entities) {
                if (entity_colision.type == "__tile__") {
                    // HANDLE COLLISION
                    if (std::any_cast<int>(entity.instance["x"]) == std::any_cast<int>(entity_colision.instance["x"]) && std::any_cast<int>(entity.instance["y"]) == std::any_cast<int>(entity_colision.instance["y"])) {
                        std::cout << "COLISION" << std::endl;
                        if (std::any_cast<int>(entity.instance["hp"]) != 0) {
                            entity.instance["hp"] = std::any_cast<int>(entity.instance["hp"]) - 1;
                            GenericCommunication new_com = GenericCommunication(CommunicationTypes::Type_NewHitBetweenElements);
                        }
                    }
                }
            }
        }
    }
}

void Game::endGame()
{
}
