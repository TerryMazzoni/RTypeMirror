/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** NewMissilesPosition
*/

#pragma once

#include "Position.hpp"
#include "ACommunication.hpp"
#include <vector>

class Missile {
    public:
        /**
         * @brief Construct a new Missile object
         * 
         */
        Missile() = default;
        /**
         * @brief Destroy the Missile object
         * 
         */
        ~Missile() = default;
        /**
         * @brief 
         * 
         * @tparam Archive 
         * @param ar 
         * @param version 
         */
        template <class Archive>
        void serialize(Archive& ar, const unsigned int version) {
            ar & _position;
            ar & _direction;
            ar & _rect;
            ar & _speed;
            ar & _damage;
            ar & _id;
        }
    private:
        Position _position;
        Position _direction;
        Position _rect;
        float _speed;
        int _damage;
        int _id;
};

class NewMissilesPosition : public ACommunication {
    public:
        /**
         * @brief Construct a new New Missiles Position object
         * 
         */
        NewMissilesPosition() {_type = CommunicationTypes::Type_NewMissilesPosition;};
        /**
         * @brief Destroy the New Missiles Position object
         * 
         */
        ~NewMissilesPosition() = default;
        /**
         * @brief Get the Type object
         * 
         * @return CommunicationTypes 
         */
        CommunicationTypes getType() const override {
            return _type;
        };
        /**
         * @brief Get the Missiles object
         * 
         * @return std::vector<Missile> 
         */
        std::vector<Missile> getMissiles() const {
            return _missiles;
        }
        /**
         * @brief Set the Missiles object
         * 
         * @param missiles 
         */
        void setMissiles(std::vector<Missile> missiles) {
            _missiles = missiles;
        }
        /**
         * @brief Get the Team object
         * 
         * @return int 
         */
        int getTeam() const {
            return _team;
        }
        /**
         * @brief Set the Team object
         * 
         * @param team 
         */
        void setTeam(int team) {
            _team = team;
        }
        /**
         * @brief 
         * 
         * @tparam Archive 
         * @param ar 
         * @param version 
         */
        template <class Archive>
        void serialize(Archive& ar, const unsigned int version) {
            ar & _missiles;
            ar & _team;
            ar & _code;
            ar & _type;
        }
    protected:
    private:
        std::vector<Missile> _missiles;
        int _team;
};
