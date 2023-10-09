/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Game
*/

#pragma once

#include "Server.hpp"
#include "../Parser.hpp"
#include "Bullet.hpp"
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
         * @brief Init the game and load the map.
         *
         * @param map_path
         */
        void initGame(std::string map_path);
        /**
         * @brief Update the game with the inputs of the players.
         *
         * @param inputs
         */
        void updateGame(std::shared_ptr<Server> server);
        /**
         * @brief End the game.
         *
         */
        void endGame();
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
        std::vector<Parser::entity_t> _entities;
        int _nb_players;
        bool _init;
};
