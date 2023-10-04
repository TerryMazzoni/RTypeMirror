/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** GameGestion
*/

#pragma once

#include "../Parser.hpp"
<<<<<<< HEAD
#include "Communication.hpp"
#include <vector>
#include <string>
=======
#include <chrono>
>>>>>>> a6c05b9 (Started to implement GameGestion.)

class GameGestion {
    public:
        GameGestion(int nb_players, std::vector<Parser::entity_t> player_info, std::string map_path);
        ~GameGestion();
        void initGame(std::string map_path);
        void updateGame(std::vector<Communication::Input>);
        void endGame();
<<<<<<< HEAD
        std::vector<Communication::Input> getCommunications() const;

=======
        std::vector<std::pair<int, GenericCommunication>> getCommunications() const;
        std::chrono::duration<double> getElapsedTime() const;
>>>>>>> a6c05b9 (Started to implement GameGestion.)
    protected:
    private:
        std::vector<Parser::entity_t> _entities;
        int _nb_players;
<<<<<<< HEAD
        std::vector<Communication::Input> _communications;
=======
        std::vector<std::pair<int, GenericCommunication>> _communications;
        std::chrono::time_point<std::chrono::system_clock> _start;
        std::chrono::time_point<std::chrono::system_clock> _end;
        std::chrono::duration<double> _elapsed_seconds;
>>>>>>> a6c05b9 (Started to implement GameGestion.)
};
