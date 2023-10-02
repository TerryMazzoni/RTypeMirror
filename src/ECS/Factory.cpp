/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Factory
*/

#include <functional>
#include <string>

#include "Component.hpp"
#include "Factory.hpp"
#include "Color.hpp"
#include "Position.hpp"
#include "Rotation.hpp"
#include "Scale.hpp"
#include "Text.hpp"
#include "Texture.hpp"

std::shared_ptr<ECS::IComponent> ECS::Factory::createColor(const std::string &value)
{
    int r = std::stoi(value.substr(0, value.find(",")));
    int g = std::stoi(value.substr(value.find(",") + 1, value.find(",", value.find(",") + 1)));
    int b = std::stoi(value.substr(value.find(",", value.find(",") + 1) + 1, value.find(",", value.find(",", value.find(",") + 1) + 1)));

    return (std::make_shared<ECS::Component<ECS::Color>>(ECS::Color(r, g, b)));
}

std::shared_ptr<ECS::IComponent> ECS::Factory::createPosition(const std::string &value)
{
    float x = std::stof(value.substr(0, value.find(",")));
    float y = std::stof(value.substr(value.find(",") + 1, value.find(",", value.find(",") + 1)));

    return (std::make_shared<ECS::Component<ECS::Position>>(ECS::Position(x, y)));
}

std::shared_ptr<ECS::IComponent> ECS::Factory::createRotation(const std::string &value)
{
    float angle = std::stoi(value);

    return (std::make_shared<ECS::Component<ECS::Rotation>>(ECS::Rotation(angle)));
}

std::shared_ptr<ECS::IComponent> ECS::Factory::createScale(const std::string &value)
{
    float scale = std::stof(value);

    return (std::make_shared<ECS::Component<ECS::Scale>>(ECS::Scale(scale)));
}

std::shared_ptr<ECS::IComponent> ECS::Factory::createText(const std::string &value)
{
    return (std::make_shared<ECS::Component<ECS::Text>>(ECS::Text(value)));
}

std::shared_ptr<ECS::IComponent> ECS::Factory::createTexture(const std::string &value)
{
    return (std::make_shared<ECS::Component<ECS::Texture>>(ECS::Texture(value)));
}

std::shared_ptr<ECS::IComponent> ECS::Factory::createComponent(ComponentType type, const std::string &value)
{
    static ECS::Factory singleton;
    static std::function<std::shared_ptr<ECS::IComponent>(ECS::Factory &, const std::string &)> funcs[6] = {
        &ECS::Factory::createColor,
        &ECS::Factory::createPosition,
        &ECS::Factory::createRotation,
        &ECS::Factory::createScale,
        &ECS::Factory::createTexture,
        &ECS::Factory::createText,
    };
    if (type >= ComponentType::Color and type <= ComponentType::Texture)
        return funcs[static_cast<int>(type)](singleton, value);
    else
        return nullptr;
}

ECS::Factory::Factory()
{
}
