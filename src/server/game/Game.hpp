/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Game
*/

#pragma once

#include "Bullet.hpp"
#include "Server.hpp"
#include "Ship.hpp"
#include <memory>
#include <vector>

class Game {
    public:
        /**
         * @brief Construct a new Game object
         */
        Game();
        /**
         * @brief Destroy the Game object
         */
        ~Game();
        /**
         * @brief Run the game
         *
         * @param server
         */
        void run(std::shared_ptr<Server> server);
        /**
         * @brief Add a ship to the game
         *
         * @param ship
         */
        void addShip(Ship ship);
        /**
         * @brief Add a ship to the game
         *
         * @param ship
         */
        void addShip(std::shared_ptr<Ship> ship);
        /**
         * @brief Add a bullet to the game
         *
         * @param bullet
         */
        void addBullet(Bullet bullet);
        /**
         * @brief Add a bullet to the game
         *
         * @param bullet
         */
        void addBullet(std::shared_ptr<Bullet> bullet);
        /**
         * @brief Remove a ship from the game
         *
         * @param id
         */
        void removeShip(int id);
        /**
         * @brief Remove a bullet from the game
         *
         * @param id
         */
        void removeBullet(int id);
        /**
         * @brief Set the Level object
         *
         * @param level
         */
        void setLevel(int level);
        /**
         * @brief Set the Score object
         *
         * @param score
         */
        void setScore(int score);
        /**
         * @brief Get the Level object
         *
         * @return int
         */
        int getLevel() const;
        /**
         * @brief Get the Score object
         *
         * @return int
         */
        int getScore() const;
        /**
         * @brief Get the Ships object
         *
         * @return std::vector<Ship>
         */
        std::vector<std::shared_ptr<Ship>> getShips() const;
        /**
         * @brief Get the Bullets object
         *
         * @return std::vector<Bullet>
         */
        std::vector<std::shared_ptr<Bullet>> getBullets() const;
        /**
         * @brief Send the ships to the clients
         *
         * @param server
         */
        void sendShips(std::shared_ptr<Server> server);
        /**
         * @brief Send the bullets to the clients
         *
         * @param server
         */
        void sendBullets(std::shared_ptr<Server> server);

    private:
        int _level;
        int _score;
        std::vector<std::shared_ptr<Ship>> _ships;
        std::vector<std::shared_ptr<Bullet>> _bullets;
};
