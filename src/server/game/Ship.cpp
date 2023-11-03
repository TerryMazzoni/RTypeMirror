/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Ship
*/

#include "Ship.hpp"

Server::Ship::Ship()
{
    _pos = Communication::Position{0, 0};
    _speed = 0;
    _life = 100;
    _id = 0;
    _level = 1;
    _type = ShipType::UNKNOW;
}

Server::Ship::Ship(Communication::Position pos, int id, ShipType type, float scale)
{
    _pos = pos;
    _speed = 0;
    _life = 100;
    _id = id;
    _level = 1;
    _scale = scale;
    _type = type;
}

Server::Ship::~Ship()
{
}

void Server::Ship::setPos(Communication::Position pos)
{
    _pos = pos;
}

void Server::Ship::setSpeed(float speed)
{
    _speed = speed;
}

void Server::Ship::setLife(float life)
{
    _life = life;
}

void Server::Ship::setId(int id)
{
    _id = id;
}

void Server::Ship::setLevel(int level)
{
    _level = level;
}

void Server::Ship::setType(ShipType type)
{
    _type = type;
}

Communication::Position Server::Ship::getPos() const
{
    return _pos;
}

float Server::Ship::getSpeed() const
{
    return _speed;
}

float Server::Ship::getLife() const
{
    return _life;
}

int Server::Ship::getId() const
{
    return _id;
}

int Server::Ship::getLevel() const
{
    return _level;
}

float Server::Ship::getScale() const
{
    return _scale;
}

ShipType Server::Ship::getType() const
{
    return _type;
}
