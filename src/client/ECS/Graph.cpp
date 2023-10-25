/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Graph
*/

#include <set>
#include <iostream>
#include "RlInputs.hpp"
#include "RlDraw.hpp"
#include "Graph.hpp"
#include "RlSprite.hpp"
#include "RlWindow.hpp"

namespace Graphic {
    std::set<Input> Graph::getInputs() const
    {
        return Raylib::getInputs();
    }

    int Graph::displayEntities(std::vector<std::optional<ECS::Entity>> entities)
    {
        Raylib::beginDraw();
        for (std::optional<ECS::Entity> &entity : entities) {
            if (entity.has_value()) {
                if (entity.value().getComponent(ComponentType::Sprite) != nullptr) {
                    displayTexture(entity.value());
                }
            }
        }
        Raylib::endDraw();
        return 0;
    }

    int Graph::displayTexture(ECS::Entity &entity)
    {
        std::shared_ptr<ECS::Sprite> sprite = std::dynamic_pointer_cast<ECS::Sprite>(entity.getComponent(ComponentType::Sprite));

        std::vector<Texture2D> textures;
        for (const auto &anyTexture : sprite->getTexturesToDisplay()) {
            textures.push_back(std::any_cast<Texture2D>(anyTexture));
        }
        Vector2 pos = Vector2({(float) sprite->getPosX(), (float) sprite->getPosY()});
        Vector2 transform = Vector2({(float) sprite->getRotation(), (float) sprite->getScale()});
        Color color = Color{(unsigned char)sprite->getR(), (unsigned char)sprite->getG(), (unsigned char)sprite->getB(), (unsigned char)sprite->getA()};

        for (auto &texture : textures) {
            Raylib::drawEx(texture, pos, transform, color);
        }
        return 0;
    }

    Graph::Graph()
    {
    }

    Graph::~Graph()
    {
    }
    std::shared_ptr<ECS::Sprite> createSprite()
    {
        return std::make_shared<Raylib::RlSprite>(Raylib::RlSprite());
    }

    std::shared_ptr<ECS::Sprite> createSprite(const int x, const int y)
    {
        return std::make_shared<Raylib::RlSprite>(Raylib::RlSprite(x, y));
    }

    std::shared_ptr<ECS::Sprite> createSprite(const std::vector<std::string> pathTextures, std::vector<int> textureIndexes)
    {
        return std::make_shared<Raylib::RlSprite>(Raylib::RlSprite(pathTextures, textureIndexes));
    }

    void createWindow(int width, int heigth, std::string name, int frameRate)
    {
        Raylib::initWindow(width, heigth, name, frameRate);
    }

    void closeWindow()
    {
        Raylib::closeWindow();
    }

    void refreshWindow()
    {
        Raylib::clear(Color({0, 0, 0, 255}));
    }

    bool checkWindowOpen()
    {
        return !Raylib::windowShouldClose();
    }
} // namespace Graphic
