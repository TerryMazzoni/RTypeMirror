/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** NewEnnemiesPosition
*/

#pragma once

#include "Position.hpp"
#include "Communication.hpp"
#include <vector>

class NewEnnemiesPosition : public Communication {
    public:
        NewEnnemiesPosition() : Communication(0) {_type = CommunicationTypes::NewEnnemiesPosition;};
        ~NewEnnemiesPosition() = default;
        template <class Archive>
        void serialize(Archive& ar, const unsigned int version) {
            ar & _positions;
            ar & _code;
        };
    protected:
    private:
        std::vector<Position> _positions;
};
