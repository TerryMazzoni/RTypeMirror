/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** main
*/

#include "Parser.hpp"

int main(void)
{
    std::vector<Parser::entity_t> entities;

    try {
        entities = Parser::ParserJson("map.json").parse().getEntities();
    } catch (Parser::ParserException &e) {
        std::cout << e.what() << std::endl;
        return 84;
    }

    for (auto &entity : entities) {
        std::cout << "type: " << entity.type << std::endl;
        std::cout << "texture: " << entity.texture << std::endl;

        for (auto &instance : entity.instance) {
            switch (entity.instanceType[instance.first]) {
                case Parser::type_t::INT:
                    std::cout << "INT    -> KEY: " << instance.first << " DATA: " << std::any_cast<int>(instance.second);
                    break;
                case Parser::type_t::FLOAT:
                    std::cout << "FLOAT  -> KEY: " << instance.first << " DATA: " << std::any_cast<float>(instance.second);
                    break;
                case Parser::type_t::STRING:
                    std::cout << "STRING -> KEY: " << instance.first << " DATA: " << std::any_cast<std::string>(instance.second);
                    break;
                default:
                    std::cout << "none";
                    break;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    return 0;
}