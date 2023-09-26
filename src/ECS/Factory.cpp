/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Factory
*/

#include <functional>
#include <string>

#include "Factory.hpp"
#include "Color.hpp"

ECS::Entity ECS::Factory::createEntity(const std::string &value)
{
    ECS::Entity entity;
    int tmp = std::stoi(value.substr(0, value.find(" ")));

    while (value.find(" ") != std::string::npos)
    {
        entity.components.push_back(_components[tmp]);
        value.substr(value.find(" ") + 1);
        tmp = std::stoi(value.substr(0, value.find(" ")));
    }
    return entity;
}

void ECS::Factory::createColor(const std::string &value)
{
    std::shared_ptr<ECS::IComponent<std::any>> color = std::make_shared<ECS::Color>();
    int r = std::stoi(value.substr(0, value.find(",")));
    int g = std::stoi(value.substr(value.find(",") + 1, value.find(",", value.find(",") + 1)));
    int b = std::stoi(value.substr(value.find(",", value.find(",") + 1) + 1, value.find(",", value.find(",", value.find(",") + 1) + 1)));
    Raylib::RlColor rlColor(r, g, b);
    color->setValue(rlColor);
    _components.push_back(color);
}

void ECS::Factory::createPosition(const std::string &value)
{
    (void)value;
}

void ECS::Factory::createRotation(const std::string &value)
{
    (void)value;
}

void ECS::Factory::createScale(const std::string &value)
{
    (void)value;
}

void ECS::Factory::createText(const std::string &value)
{
    (void)value;
}

void ECS::Factory::createTexture(const std::string &value)
{
    (void)value;
}

std::optional<ECS::Entity> ECS::Factory::createEntity(ComponentType type, const std::string &value)
{
    static ECS::Factory singleton;
    static std::function<void(ECS::Factory &, const std::string &)> funcs[6] = {
        &ECS::Factory::createColor,
        &ECS::Factory::createPosition,
        &ECS::Factory::createRotation,
        &ECS::Factory::createScale,
        &ECS::Factory::createText,
        &ECS::Factory::createTexture,
    };
    if (type == ComponentType::Entity)
        return singleton.createEntity(value);
    else if (type >= ComponentType::Color and type <= ComponentType::Texture)
        funcs[static_cast<int>(type)](singleton, value);
    return std::nullopt;
}

ECS::Factory::Factory()
{
}
