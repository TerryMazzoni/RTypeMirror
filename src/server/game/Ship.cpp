/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Ship
*/

#include "Ship.hpp"

Ship::Ship()
{
    _pos = Communication::Position{0, 0};
    _speed = 0;
    _life = 100;
    _id = 0;
    _level = 1;
    _type = ShipType::UNKNOW;
}

Ship::Ship(Communication::Position pos, int id, ShipType type)
{
    _pos = pos;
    _speed = 0;
    _life = 100;
    _id = id;
    _level = 1;
    _type = type;
}

Ship::~Ship()
{
}

void Ship::setPos(Communication::Position pos)
{
    _pos = pos;
}

void Ship::setSpeed(float speed)
{
    _speed = speed;
}

void Ship::setLife(float life)
{
    _life = life;
}

void Ship::setId(int id)
{
    _id = id;
}

void Ship::setLevel(int level)
{
    _level = level;
}

void Ship::setType(ShipType type)
{
    _type = type;
}

Communication::Position Ship::getPos() const
{
    return _pos;
}

float Ship::getSpeed() const
{
    return _speed;
}

float Ship::getLife() const
{
    return _life;
}

int Ship::getId() const
{
    return _id;
}

int Ship::getLevel() const
{
    return _level;
}

ShipType Ship::getType() const
{
    return _type;
}
