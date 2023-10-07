/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** GameGestion
*/

#include "GameGestion.hpp"

GameGestion::GameGestion(int nb_players, std::vector<Parser::entity_t> player_info, std::string map_path)
{
    _nb_players = nb_players;
    Parser::ParserJson parser = Parser::ParserJson(map_path);
    parser.parse();
    if (parser.getEntities().size() == 0)
        throw std::runtime_error("Error: no entities in map");
    _entities = parser.getEntities();
    for (auto &entity : player_info) {
        _entities.push_back(entity);
    }
    initGame(map_path);
}

GameGestion::~GameGestion()
{
}

void GameGestion::initGame(std::string map_path)
{
    for (auto &entity : _entities) {
        std::cout << "Entity: " << entity.type << std::endl;
    }
    GenericCommunication new_com = GenericCommunication(CommunicationTypes::Type_NewMap);
    new_com.setMap(map_path);
    for (int i = 0; i < _nb_players; i++)
        _communications.push_back(std::make_pair(i, new_com));
}

void GameGestion::updateGame(std::vector<Communication::Input> communications)
{
    for (auto &entity : _entities) {
        if (entity.type != "player") {
            entity.instance["x"] = std::any_cast<int>(entity.instance["x"]) + 1;
            std::cout << "Entity: " << entity.type << " x: " << std::any_cast<int>(entity.instance["x"]) << std::endl;
        }
        for (auto &communication : communications) {
            if (std::any_cast<int>(entity.instance["id"]) == communication.first) {
                // HANDLE PLAYER POSITION OR ACTION
            }
        }
        if (entity.type != "__tile__") {
            for (auto &entity_colision : _entities) {
                if (entity_colision.type == "__tile__") {
                    // HANDLE COLLISION
                    if (std::any_cast<int>(entity.instance["x"]) == std::any_cast<int>(entity_colision.instance["x"]) && std::any_cast<int>(entity.instance["y"]) == std::any_cast<int>(entity_colision.instance["y"])) {
                        std::cout << "COLISION" << std::endl;
                        if (std::any_cast<int>(entity.instance["hp"]) != 0) {
                            entity.instance["hp"] = std::any_cast<int>(entity.instance["hp"]) - 1;
                            GenericCommunication new_com = GenericCommunication(CommunicationTypes::Type_NewHitBetweenElements);
                        }
                    }
                }
            }
        }
    }
}

std::vector<Communication::Input> GameGestion::getCommunications() const
{
    return _communications;
}