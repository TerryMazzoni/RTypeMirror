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
        Missile() = default;
        ~Missile() = default;
        template <class Archive>
        void serialize(Archive& ar, const unsigned int version) {
            ar & _position;
            ar & _direction;
            ar & _rect;
            ar & _speed;
            ar & _damage;
            ar & _id;
        };
    private:
        Position _position;
        Position _direction;
        Position _rect;
        float _speed;
        int _damage;
        int _id;
};

class NewMissilesPosition : Communication {
    public:
        NewMissilesPosition() : Communication(0) {_type = CommunicationTypes::NewPlayerPosition;};
        ~NewMissilesPosition() = default;
        template <class Archive>
        void serialize(Archive& ar, const unsigned int version) {
            ar & _missiles;
            ar & _team;
            ar & _code;
        };
    protected:
    private:
        std::vector<Missile> _missiles;
        int _team;
};
