/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Bullet
*/

#include "Bullet.hpp"

Server::Bullet::Bullet()
{
    _pos = Communication::Position{0, 0};
    _direction = Communication::Position{0, 0};
    _speed = 0;
    _damage = 0;
    _id = 0;
}

Server::Bullet::Bullet(Communication::Position pos, Communication::Position direction, float speed, float damage, int id)
{
    _pos = pos;
    _direction = direction;
    _speed = speed;
    _damage = damage;
    _id = id;
}

Server::Bullet::~Bullet()
{
}

void Server::Bullet::setPos(Communication::Position pos)
{
    _pos = pos;
}

void Server::Bullet::setDirection(Communication::Position direction)
{
    _direction = direction;
}

void Server::Bullet::setSpeed(float speed)
{
    _speed = speed;
}

void Server::Bullet::setDamage(float damage)
{
    _damage = damage;
}

void Server::Bullet::setId(int id)
{
    _id = id;
}

void Server::Bullet::setTeam(int team)
{
    _team = team;
}

Communication::Position Server::Bullet::getPos() const
{
    return _pos;
}

Communication::Position Server::Bullet::getDirection() const
{
    return _direction;
}

float Server::Bullet::getSpeed() const
{
    return _speed;
}

float Server::Bullet::getDamage() const
{
    return _damage;
}

int Server::Bullet::getId() const
{
    return _id;
}

int Server::Bullet::getTeam() const
{
    return _team;
}
