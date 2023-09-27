/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** NewPlayerPosition
*/

#pragma once

#include "Position.hpp"
#include "ACommunication.hpp"

class NewPlayerPosition : public ACommunication {
    public:
        /**
         * @brief Construct a new New Player Position object
         * 
         */
        NewPlayerPosition() : _position(Position(Coords{0,1}, Coords{1, 2})) {
            _type = CommunicationTypes::Type_NewPlayerPosition;
        };
        /**
         * @brief Construct a new New Player Position object
         * 
         * @param pos 
         */
        NewPlayerPosition(Position pos) : _position(Position(Coords{0,1}, Coords{1, 2})) {
            _position = pos;
            _type = CommunicationTypes::Type_NewPlayerPosition;
        };
        /**
         * @brief Destroy the New Player Position object
         * 
         */
        ~NewPlayerPosition() = default;
        /**
         * @brief Get the Type object
         * 
         * @return CommunicationTypes 
         */
        CommunicationTypes getType() const override {
            return _type;
        }
        /**
         * @brief Get the Position object
         * 
         * @return Position 
         */
        Position getPosition() const {return _position;};
        /**
         * @brief Set the Position object
         * 
         * @param pos 
         */
        void setPosition(Position pos) {_position = pos;};
        /**
         * @brief 
         * 
         * @tparam Archive 
         * @param ar 
         * @param version 
         */
        template <class Archive>
        void serialize(Archive& ar, const unsigned int version) {
            (void)version;
            ar & _position;
            ar & _code;
            ar & _type;
        }
    protected:
    private:
        Position _position;
};
