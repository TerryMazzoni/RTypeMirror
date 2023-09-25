/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** NewPlayerPosition
*/

#pragma once

#include "Position.hpp"
#include "Communication.hpp"

class NewPlayerPosition : public Communication {
    public:
        NewPlayerPosition() : Communication(0) {_type = CommunicationTypes::NewPlayerPosition;};
        ~NewPlayerPosition() = default;
        template <class Archive>
        void serialize(Archive& ar, const unsigned int version) {
            ar & _position;
            ar & _code;
        }
    protected:
    private:
        Position _position;
};
