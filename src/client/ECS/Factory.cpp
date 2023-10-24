/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Factory
*/

#include <functional>
#include <string>
#include <iostream>
#include "Graph.hpp"
#include "Component.hpp"
#include "Factory.hpp"
#include "Sprite.hpp"

std::shared_ptr<ECS::IComponent> ECS::Factory::createSprite(const std::string &value)
{
    std::vector<std::string> text;
    std::vector<std::string> textures;
    std::vector<int> indexes;
    int j = 0;
    bool digit = false;

    for (size_t i = 0; i < value.size(); i++) {
        if (value[i] == ',') {
            text.push_back(value.substr(j, i - j));
            j = i + 1;
        }
    }
    text.push_back(value.substr(j, value.size()));
    j = 0;
    for (auto val : text) {
        for (size_t i = 0; i < val.length(); i++) {
            if (!(digit = isdigit(val[i]))) {
                break;
            }
        }
        if (digit == true && val.length() > 0)
            indexes.push_back(std::stoi(val));
        else
            textures.push_back(val);
        j++;
    }
    if (indexes.empty())
        indexes = {0};
    return (Graphic::createSprite(textures, indexes));
}

std::shared_ptr<ECS::IComponent> ECS::Factory::createComponent(ComponentType type, const std::string &value)
{
    static ECS::Factory singleton;
    static std::function<std::shared_ptr<ECS::IComponent>(ECS::Factory &, const std::string &)> funcs[6] = {
        &ECS::Factory::createSprite,
    };
    if (type <= static_cast<ComponentType>(5))
        return funcs[static_cast<int>(type)](singleton, value);
    else
        return nullptr;
}

ECS::Factory::Factory()
{
}
