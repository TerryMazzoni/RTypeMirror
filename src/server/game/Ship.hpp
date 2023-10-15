/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Ship
*/

#pragma once

#include "Communication.hpp"

class Ship {
    public:
        /**
         * @brief Construct a new Ship object
         */
        Ship();
        /**
         * @brief Construct a new Ship object
         *
         * @param pos
         * @param id
         * @param type
         */
        Ship(Communication::Position pos, int id, ShipType type);
        /**
         * @brief Destroy the Ship object
         */
        ~Ship();
        /**
         * @brief Set the Pos object
         *
         * @param pos
         */
        void setPos(Communication::Position pos);
        /**
         * @brief Set the Speed object
         *
         * @param speed
         */
        void setSpeed(float speed);
        /**
         * @brief Set the Life object
         *
         * @param life
         */
        void setLife(float life);
        /**
         * @brief Set the Id object
         *
         * @param id
         */
        void setId(int id);
        /**
         * @brief Set the Level object
         *
         * @param level
         */
        void setLevel(int level);
        /**
         * @brief Set the Type object
         *
         * @param type
         */
        void setType(ShipType type);
        /**
         * @brief Get the Pos object
         *
         * @return Communication::Position
         */
        Communication::Position getPos() const;
        /**
         * @brief Get the Speed object
         *
         * @return float
         */
        float getSpeed() const;
        /**
         * @brief Get the Life object
         *
         * @return float
         */
        float getLife() const;
        /**
         * @brief Get the Id object
         *
         * @return int
         */
        int getId() const;
        /**
         * @brief Get the Level object
         *
         * @return int
         */
        int getLevel() const;
        /**
         * @brief Get the Type object
         *
         * @return ShipType
         */
        ShipType getType() const;

    private:
        Communication::Position _pos;
        float _speed;
        float _life;
        int _id;
        int _level;
        ShipType _type;
};
