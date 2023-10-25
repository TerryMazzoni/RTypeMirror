/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Bonus
*/

#pragma once

#include "Communication.hpp"

class Bonus {
    public:
        /**
         * @brief Construct a new Bonus object
         */
        Bonus();
        /**
         * @brief Construct a new Bonus object
         *
         * @param pos
         * @param id
         * @param type
         */
        Bonus(Communication::Position pos, int id, BonusType type);
        /**
         * @brief Destroy the Bonus object
         */
        ~Bonus();
        /**
         * @brief Set the Pos object
         *
         * @param pos
         */
        void setPos(Communication::Position pos);
        /**
         * @brief Set the Id object
         *
         * @param id
         */
        void setId(int id);
        /**
         * @brief Set the Type object
         *
         * @param type
         */
        void setType(BonusType type);
        /**
         * @brief Get the Pos object
         *
         * @return Communication::Position
         */
        Communication::Position getPos() const;
        /**
         * @brief Get the Id object
         *
         * @return int
         */
        int getId() const;
        /**
         * @brief Get the Type object
         *
         * @return BonusType
         */
        BonusType getType() const;

    private:
        Communication::Position _pos;
        int _id;
        BonusType _type;
};
