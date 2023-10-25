/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Bonus
*/

#include "Bonus.hpp"

Bonus::Bonus()
{
    _pos = Communication::Position{0, 0};
    _id = 0;
    _type = BonusType::UNKNOW;
}

Bonus::Bonus(Communication::Position pos, int id, BonusType type)
{
    _pos = pos;
    _id = id;
    _type = type;
}

Bonus::~Bonus()
{
}

void Bonus::setPos(Communication::Position pos)
{
    _pos = pos;
}

void Bonus::setId(int id)
{
    _id = id;
}

void Bonus::setType(BonusType type)
{
    _type = type;
}

Communication::Position Bonus::getPos() const
{
    return _pos;
}

int Bonus::getId() const
{
    return _id;
}

BonusType Bonus::getType() const
{
    return _type;
}
