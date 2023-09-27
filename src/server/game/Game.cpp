/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Game
*/

#include "Game.hpp"

Game::Game()
{
    _level = 0;
    _score = 0;
}

Game::~Game()
{
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
    for (auto it = _ships.begin(); it != _ships.end(); it++)
    {
        if ((*it)->getId() == id)
        {
            _ships.erase(it);
            return;
        }
    }
}

void Game::removeBullet(int id)
{
    for (auto it = _bullets.begin(); it != _bullets.end(); it++)
    {
        if ((*it)->getId() == id)
        {
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
