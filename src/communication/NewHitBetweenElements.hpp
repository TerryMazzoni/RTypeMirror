/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** NewHitBetweenElements
*/

#pragma once

#include "Position.hpp"
#include "ACommunication.hpp"
#include <vector>

enum class ColisionTypes {
    Player,
    Ennemy,
    Missile,
    Mate,
};

class Colision {
    public:
        /**
         * @brief Construct a new Colision object
         * 
         */
        Colision() = default;
        /**
         * @brief Construct a new Colision object
         * 
         * @param c_type 
         * @param info 
         */
        Colision(ColisionTypes c_type, int info) : _c_type(c_type), _info(info) {};
        /**
         * @brief Destroy the Colision object
         * 
         */
        ~Colision() = default;
        /**
         * @brief Get the Type object
         * 
         * @return ColisionTypes 
         */
        ColisionTypes getType() const {
            return _c_type;
        }
        /**
         * @brief Get the Info object
         * 
         * @return int 
         */
        int getInfo() const {
            return _info;
        }
        /**
         * @brief Set the Type object
         * 
         * @param c_type 
         */
        void setType(ColisionTypes c_type) {
            _c_type = c_type;
        }
        /**
         * @brief Set the Info object
         * 
         * @param info 
         */
        void setInfo(int info) {
            _info = info;
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
            ar & _c_type;
            ar & _info;
        }
    private:
        ColisionTypes _c_type;
        int _info;
};

class NewHitBetweenElements : public ACommunication {
    public:
        /**
         * @brief Construct a new New Hit Between Elements object
         * 
         */
        NewHitBetweenElements() {_type = CommunicationTypes::Type_NewHitBetweenElements;};
        /**
         * @brief Destroy the New Hit Between Elements object
         * 
         */
        ~NewHitBetweenElements() = default;
        /**
         * @brief Get the Type object
         * 
         * @return CommunicationTypes 
         */
        CommunicationTypes getType() const override {
            return _type;
        };
        /**
         * @brief Get the Positions object
         * 
         * @return std::vector<Position> 
         */
        std::vector<Position> getPositions() const {
            return _positions;
        }
        /**
         * @brief Set the Positions object
         * 
         * @param positions 
         */
        void setPositions(std::vector<Position> positions) {
            _positions = positions;
        }
        /**
         * @brief Get the First Colision object
         * 
         * @return Colision 
         */
        Colision getFirstColision() const {
            return _first_c;
        }
        /**
         * @brief Get the Second Colision object
         * 
         * @return Colision 
         */
        Colision getSecondColision() const {
            return _second_c;
        }
        /**
         * @brief Set the First Colision object
         * 
         * @param first_c 
         */
        void setFirstColision(Colision first_c) {
            _first_c = first_c;
        }
        /**
         * @brief Set the Second Colision object
         * 
         * @param second_c 
         */
        void setSecondColision(Colision second_c) {
            _second_c = second_c;
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
            ar & _positions;
            ar & _code;
            ar & _type;
        }
    protected:
    private:
        Colision _first_c;
        Colision _second_c;
        std::vector<Position> _positions;
};