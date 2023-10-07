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
    _ships = std::vector<std::shared_ptr<Ship>>();
    _bullets = std::vector<std::shared_ptr<Bullet>>();
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
    _ships.push_back(std::make_shared<Ship>(Communication::Position{0, 0}, 0, ShipType::PLAYER));
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
    // do things here like update positions, etc.
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
                    std::cout << "Game started" << std::endl;
                    sendShips(server);
                    server->sendToAll(timer);
                }
            }
            if (!is_running(0))
                return;
            this->run(server);
        });
    server->getIoService().run();
}

void Game::addShip(Ship ship)
{
    _ships.push_back(std::make_shared<Ship>(ship));
}

void Game::addShip(std::shared_ptr<Ship> ship)
{
    _ships.push_back(ship);
}

void Game::addBullet(Bullet bullet)
{
    _bullets.push_back(std::make_shared<Bullet>(bullet));
}

void Game::addBullet(std::shared_ptr<Bullet> bullet)
{
    _bullets.push_back(bullet);
}

void Game::removeShip(int id)
{
    for (auto it = _ships.begin(); it != _ships.end(); it++) {
        if ((*it)->getId() == id) {
            _ships.erase(it);
            return;
        }
    }
}

void Game::removeBullet(int id)
{
    for (auto it = _bullets.begin(); it != _bullets.end(); it++) {
        if ((*it)->getId() == id) {
            _bullets.erase(it);
            return;
        }
    }
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

std::vector<std::shared_ptr<Ship>> Game::getShips() const
{
    return _ships;
}

std::vector<std::shared_ptr<Bullet>> Game::getBullets() const
{
    return _bullets;
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
            std::cout << "sending" << shipsPosition.nbrItems << "ships" << std::endl;
            server->sendToAll(shipsPosition);
            shipsPosition.nbrItems = 0;
            memset(&shipsPosition.ship, 0, sizeof(shipsPosition.ship));
        }
    }
    if (shipsPosition.nbrItems > 0)
        server->sendToAll(shipsPosition);
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
    if (missilesPosition.nbrItems > 0)
        server->sendToAll(missilesPosition);
}
