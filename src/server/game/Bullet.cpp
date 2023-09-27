/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Bullet
*/

#include "Bullet.hpp"

Bullet::Bullet()
{
    _pos = Coords{0, 0};
    _direction = Coords{0, 0};
    _speed = 0;
    _damage = 0;
    _id = 0;
}

Bullet::Bullet(Coords pos, Coords direction, float speed, float damage, int id)
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

void Bullet::setPos(Coords pos)
{
    _pos = pos;
}

void Bullet::setDirection(Coords direction)
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

Coords Bullet::getPos() const
{
    return _pos;
}

Coords Bullet::getDirection() const
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
