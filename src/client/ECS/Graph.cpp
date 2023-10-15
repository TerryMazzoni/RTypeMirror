/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Graph
*/

#include <set>
#include "Graph.hpp"

std::set<Input> Graph::getInputs() const
{
    return Raylib::getInputs();
}

int Graph::displayEntities(std::vector<std::optional<ECS::Entity>> entities)
{
    for (std::optional<ECS::Entity> &entity : entities) {
        if (entity.has_value()) {
            if (entity.value().getComponent(ComponentType::Texture) != nullptr && entity.value().getComponent(ComponentType::Position) != nullptr) {
                displayTexture(entity.value());
            }
            else if (entity.value().getComponent(ComponentType::Text) != nullptr && entity.value().getComponent(ComponentType::Position) != nullptr) {
                displayText(entity.value());
            }
        }
    }
    return 0;
}

int Graph::displayTexture(ECS::Entity &entity)
{
    ECS::Color color;
    ECS::Position position;
    ECS::Rotation rotation;
    ECS::Scale scale;
    ECS::Texture texture;

    if (entity.getComponent(ComponentType::Color) != nullptr)
        color = std::any_cast<ECS::Color>(entity.getComponent(ComponentType::Color)->getValue());
    else
        color = ECS::Color(255, 255, 255);
    if (entity.getComponent(ComponentType::Rotation) != nullptr)
        rotation = std::any_cast<ECS::Rotation>(entity.getComponent(ComponentType::Rotation)->getValue());
    else
        rotation = ECS::Rotation(0);
    if (entity.getComponent(ComponentType::Scale) != nullptr)
        scale = std::any_cast<ECS::Scale>(entity.getComponent(ComponentType::Scale)->getValue());
    else
        scale = ECS::Scale(1);
    texture = std::any_cast<ECS::Texture>(entity.getComponent(ComponentType::Texture)->getValue());
    position = std::any_cast<ECS::Position>(entity.getComponent(ComponentType::Position)->getValue());
    for (auto textureID : texture.currentTexture) {
        Raylib::drawEx(texture.textureList[textureID], Vector2({position.x, position.y}), Vector2({rotation.angle, scale.scale}), color.color);
    }
    return 0;
}

int Graph::displayText(ECS::Entity &entity)
{
    ECS::Text text;
    ECS::Position position;
    ECS::Scale scale;
    ECS::Color color;

    if (entity.getComponent(ComponentType::Scale) != nullptr)
        scale = std::any_cast<ECS::Scale>(entity.getComponent(ComponentType::Scale)->getValue());
    else
        scale = ECS::Scale(1);
    if (entity.getComponent(ComponentType::Color) != nullptr)
        color = std::any_cast<ECS::Color>(entity.getComponent(ComponentType::Color)->getValue());
    else
        color = ECS::Color(255, 255, 255);
    text = std::any_cast<ECS::Text>(entity.getComponent(ComponentType::Text)->getValue());
    position = std::any_cast<ECS::Position>(entity.getComponent(ComponentType::Position)->getValue());
    Raylib::drawText(text.text, Vector3({position.x, position.y, scale.scale}), color.color);
    return 0;
}

Graph::Graph()
{
}

Graph::~Graph()
{
}
