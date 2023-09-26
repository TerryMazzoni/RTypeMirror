/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** NewMatesPosition
*/

#pragma once

#include "Position.hpp"
#include "Communication.hpp"
#include <vector>

class Mate {
    public:
        Mate() = default;
        ~Mate() = default;
    protected:
    private:
        template <class Archive>
        void serialize(Archive& ar, const unsigned int version) {
            ar & _position;
            ar & _id;
        };
        Position _position;
        int _id;
};

class NewMatesPosition : public Communication {
    public:
        NewMatesPosition() : Communication(0) {_type = CommunicationTypes::NewMatesPosition;};
        ~NewMatesPosition() = default;
    protected:
    private:
        template <class Archive>
        void serialize(Archive& ar, const unsigned int version) {
            ar & _positions;
            ar & _code;
        };
        Mate _positions;
};