/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Bonus
*/

#include "Bonus.hpp"

Server::Bonus::Bonus()
{
    _pos = Communication::Position{0, 0};
    _id = 0;
    _type = BonusType::UNKNOW;
}

Server::Bonus::Bonus(Communication::Position pos, int id, BonusType type)
{
    _pos = pos;
    _id = id;
    _type = type;
}

Server::Bonus::~Bonus()
{
}

void Server::Bonus::setPos(Communication::Position pos)
{
    _pos = pos;
}

void Server::Bonus::setId(int id)
{
    _id = id;
}

void Server::Bonus::setType(BonusType type)
{
    _type = type;
}

Communication::Position Server::Bonus::getPos() const
{
    return _pos;
}

int Server::Bonus::getId() const
{
    return _id;
}

BonusType Server::Bonus::getType() const
{
    return _type;
}
