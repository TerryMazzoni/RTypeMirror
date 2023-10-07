/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Game
*/

#pragma once

#include "Server.hpp"
#include "../Parser.hpp"
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
        void updateGame(std::vector<Communication::Input>, std::shared_ptr<Server> server);
        /**
         * @brief End the game.
         *
         */
        void endGame();

    private:
        int _level;
        int _score;
        std::vector<Parser::entity_t> _entities;
        int _nb_players;
        bool _init;
};
