/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Game
*/

#pragma once

#include "Bullet.hpp"
#include "Ship.hpp"
#include <memory>
#include <vector>

class Game
{
public:
    Game();
    ~Game();
    void addShip(Ship ship);
    void addShip(std::shared_ptr<Ship> ship);
    void addBullet(Bullet bullet);
    void addBullet(std::shared_ptr<Bullet> bullet);
    void removeShip(int id);
    void removeBullet(int id);
    void setLevel(int level);
    void setScore(int score);
    int getLevel() const;
    int getScore() const;
    std::vector<std::shared_ptr<Ship>> getShips() const;
    std::vector<std::shared_ptr<Bullet>> getBullets() const;

private:
    int _level;
    int _score;
    std::vector<std::shared_ptr<Ship>> _ships;
    std::vector<std::shared_ptr<Bullet>> _bullets;
};
