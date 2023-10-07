/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** GameGestion
*/

#pragma once

#include "Parser.hpp"
#include "Communication.hpp"
#include <vector>
#include <string>

class GameGestion {
    public:
        GameGestion(int nb_players, std::vector<Parser::entity_t> player_info, std::string map_path);
        ~GameGestion();
        void initGame(std::string map_path);
        void updateGame(std::vector<Communication::Input>);
        void endGame();
        std::vector<Communication::Input> getCommunications() const;

    protected:
    private:
        std::vector<Parser::entity_t> _entities;
        int _nb_players;
        std::vector<Communication::Input> _communications;
};
