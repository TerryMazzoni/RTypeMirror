/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** NewMatesPosition
*/

#pragma once

#include "Position.hpp"
#include "ACommunication.hpp"
#include <vector>

class Mate {
    public:
        /**
         * @brief Construct a new Mate object
         * 
         */
        Mate() = default;
        /**
         * @brief Construct a new Mate object
         * 
         * @param pos 
         * @param id 
         */
        Mate(Position pos, int id) : _position(pos), _id(id) {};
        /**
         * @brief Destroy the Mate object
         * 
         */
        ~Mate() = default;
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
            ar & _id;
        }
    protected:
    private:
        Position _position;
        int _id;
};

class NewMatesPosition : public ACommunication {
    public:
        /**
         * @brief Construct a new New Mates Position object
         * 
         */
        NewMatesPosition() {_type = CommunicationTypes::Type_NewMatesPosition;};
        /**
         * @brief Destroy the New Mates Position object
         * 
         */
        ~NewMatesPosition() = default;
        /**
         * @brief Get the Type object
         * 
         * @return CommunicationTypes 
         */
        CommunicationTypes getType() const override {
            return _type;
        };
        /**
         * @brief Get the Mate information object
         * 
         * @return std::vector<Mate>
         */
        std::vector<Mate> getMate() const {
            return _mates;
        }
        /**
         * @brief Set the Mate information object
         * 
         * @param mates 
         */
        void setMate(std::vector<Mate> mates) {
            _mates = mates;
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
            ar & _mates;
            ar & _code;
            ar & _type;
        }
    protected:
    private:
        std::vector<Mate> _mates;
};