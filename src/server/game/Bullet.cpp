/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Bullet
*/

#include "Bullet.hpp"

Bullet::Bullet()
{
    _pos = Communication::Position{0, 0};
    _direction = Communication::Position{0, 0};
    _speed = 0;
    _damage = 0;
    _id = 0;
}

Bullet::Bullet(Communication::Position pos, Communication::Position direction, float speed, float damage, int id)
{
    _pos = pos;
    _direction = direction;
    _speed = speed;
    _damage = damage;
    _id = id;
}

Bullet::~Bullet()
{
}

void Bullet::setPos(Communication::Position pos)
{
    _pos = pos;
}

void Bullet::setDirection(Communication::Position direction)
{
    _direction = direction;
}

void Bullet::setSpeed(float speed)
{
    _speed = speed;
}

void Bullet::setDamage(float damage)
{
    _damage = damage;
}

void Bullet::setId(int id)
{
    _id = id;
}

void Bullet::setTeam(int team)
{
    _team = team;
}

Communication::Position Bullet::getPos() const
{
    return _pos;
}

Communication::Position Bullet::getDirection() const
{
    return _direction;
}

float Bullet::getSpeed() const
{
    return _speed;
}

float Bullet::getDamage() const
{
    return _damage;
}

int Bullet::getId() const
{
    return _id;
}

int Bullet::getTeam() const
{
    return _team;
}
