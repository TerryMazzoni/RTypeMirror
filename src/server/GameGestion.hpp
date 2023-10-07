/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** GameGestion
*/

#pragma once

#include <string>
#include "../communication/GenericCommunication.hpp"
#include "../Parser.hpp"

class GameGestion {
    public:
        GameGestion(int nb_players, std::vector<Parser::entity_t> player_info, std::string map_path);
        ~GameGestion();
        void initGame(std::string map_path);
        void updateGame(std::vector<std::pair<int, GenericCommunication>>);
        void endGame();
        std::vector<std::pair<int, GenericCommunication>> getCommunications() const;
    protected:
    private:
        std::vector<Parser::entity_t> _entities;
        int _nb_players;
        std::vector<std::pair<int, GenericCommunication>> _communications;
};
