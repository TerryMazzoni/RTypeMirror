/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Bullet
*/

#pragma once

#include "Communication.hpp"

class Bullet {
    public:
        /**
         * @brief Construct a new Bullet object
         */
        Bullet();
        /**
         * @brief Construct a new Bullet object
         *
         * @param pos
         * @param direction
         * @param speed
         * @param damage
         * @param id
         */
        Bullet(Communication::Position pos, Communication::Position direction, float speed, float damage, int id);
        /**
         * @brief Destroy the Bullet object
         */
        ~Bullet();
        /**
         * @brief Set the Pos object
         *
         * @param pos
         */
        void setPos(Communication::Position pos);
        /**
         * @brief Set the Direction object
         *
         * @param direction
         */
        void setDirection(Communication::Position direction);
        /**
         * @brief Set the Speed object
         *
         * @param speed
         */
        void setSpeed(float speed);
        /**
         * @brief Set the Damage object
         *
         * @param damage
         */
        void setDamage(float damage);
        /**
         * @brief Set the Id object
         *
         * @param id
         */
        void setId(int id);
        /**
         * @brief Set the Id of the Team
         *
         * @param team
         */
        void setTeam(int team);
        /**
         * @brief Get the Pos object
         *
         * @return Communication::Position
         */
        Communication::Position getPos() const;
        /**
         * @brief Get the Direction object
         *
         * @return Communication::Position
         */
        Communication::Position getDirection() const;
        /**
         * @brief Get the Speed object
         *
         * @return float
         */
        float getSpeed() const;
        /**
         * @brief Get the Damage object
         *
         * @return float
         */
        float getDamage() const;
        /**
         * @brief Get the Id object
         *
         * @return int
         */
        int getId() const;
        /**
         * @brief Get the Id of the Team
         *
         * @return int
         */
        int getTeam() const;

    private:
        Communication::Position _pos;
        Communication::Position _direction;
        float _speed;
        float _damage;
        int _id;
        int _team;
};
