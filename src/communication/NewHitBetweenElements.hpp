/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** NewHitBetweenElements
*/

#pragma once

#include "Position.hpp"
#include "Communication.hpp"
#include <vector>

enum class ColisionTypes {
    Player,
    Ennemy,
    Missile,
    Mate,
};

class NewHitBetweenElements : public Communication {
    public:
        NewHitBetweenElements() : Communication(0) {_type = CommunicationTypes::NewHitBetweenElements;};
        ~NewHitBetweenElements() = default;
        template <class Archive>
        void serialize(Archive& ar, const unsigned int version) {
            ar & _positions;
            ar & _code;
        };
    protected:
    private:
        std::pair<ColisionTypes, int> _first_c;
        std::pair<ColisionTypes, int> _second_c;
        std::vector<Position> _positions;
};