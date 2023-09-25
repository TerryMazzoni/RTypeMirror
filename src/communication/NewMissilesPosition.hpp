/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** NewMissilesPosition
*/

#pragma once

#include "Position.hpp"
#include "Communication.hpp"
#include <vector>

class Missile {
    public:
    private:
        Position _position;
        Position _direction;
        Position _rect;
        float _speed;
        int _damage;
};

class NewMissilesPosition : Communication {
    public:
        NewMissilesPosition() : Communication(0) {_type = CommunicationTypes::NewPlayerPosition;};
        ~NewMissilesPosition() = default;
    protected:
    private:
        std::vector<Missile> _missiles;
        int _team;
};
