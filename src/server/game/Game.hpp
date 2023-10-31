/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Game
*/

#pragma once

#include "Server.hpp"
#include "Parser.hpp"
#include "Bullet.hpp"
#include "Ship.hpp"
#include "Bonus.hpp"
#include <memory>
#include <vector>
#include <optional>

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
         * @brief Update the ships position depending on the inputs.
         *
         * @param server
         * @param entity
         */
        void updateShips(std::shared_ptr<Server> server, std::optional<Parser::entity_t> &entity);
        /**
         * @brief Update the colisions between the ships and the bullets.
         *
         * @param server
         * @param entity
         */
        void updateColisions(std::shared_ptr<Server> server, std::optional<Parser::entity_t> &entity);
        /**
         * @brief Update the entities and push it to the vectors.
         *
         * @param server
         * @param entity
         */
        void updateEntities(std::shared_ptr<Server> server, std::optional<Parser::entity_t> &entity);
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
        /**
         * @brief Send the bonus to the clients
         *
         * @param bonus
         */
        void sendBonus(std::shared_ptr<Server> server);
        /**
         * @brief Send the id of an entity to delete to the clients
         *
         * @param server
         */
        void sendDelete(std::shared_ptr<Server> server, int id);
        /**
         * @brief Check the colision between to entities.
         *
         * @return true
         * @return false
         */
        bool checkColision(std::optional<Parser::entity_t> entity1, std::optional<Parser::entity_t> entity2);

    private:
        int _level;
        int _score;
        std::vector<std::optional<Parser::entity_t>> _entities;
        int _nb_players;
        bool _init;
        std::vector<std::shared_ptr<Bullet>> _bullets;
        std::vector<std::shared_ptr<Ship>> _ships;
        std::vector<std::shared_ptr<Bonus>> _bonus;
        int _last_entity_id;
        int _tile_size;
        unsigned int _loop;
};
