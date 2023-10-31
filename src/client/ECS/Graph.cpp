/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Graph
*/

#include <set>
#include <iostream>
#include <algorithm>
#include "RlInputs.hpp"
#include "RlDraw.hpp"
#include "Graph.hpp"
#include "RlSprite.hpp"
#include "RlWindow.hpp"
#include "RlMusic.hpp"
#include "RlSound.hpp"
#include "RlTime.hpp"
#include "RlWeapon.hpp"

namespace Graphic {
    std::set<Input> Graph::getInputs() const
    {
        return Raylib::getInputs();
    }

    int Graph::displayEntities(std::vector<std::optional<ECS::Entity>> entities)
    {
        Raylib::beginDraw();
        std::vector<ECS::Entity> entitiesSorted = _sortEntities(entities);

        for (ECS::Entity &entity : entitiesSorted) {
            if (entity.getComponent(ComponentType::Sprite) != nullptr) {
                _displayTexture(entity);
            }
        }
        Raylib::endDraw();
        return 0;
    }

    std::vector<ECS::Entity> Graph::_sortEntities(std::vector<std::optional<ECS::Entity>> entities)
    {
        std::vector<ECS::Entity> listEntitiesPlayer = {};
        std::vector<ECS::Entity> listEntitiesEnemy = {};
        std::vector<ECS::Entity> listEntitiesBullet = {};
        std::vector<ECS::Entity> listEntitiesBackground1 = {};
        std::vector<ECS::Entity> listEntitiesBackground2 = {};
        std::vector<ECS::Entity> listEntitiesBackground3 = {};

        for (auto &entity : entities) {
            if (entity.has_value()) {
                switch (entity.value().id.first) {
                    case EntityType::Background1:
                        listEntitiesBackground1.push_back(entity.value());
                        break;
                    case EntityType::Background2:
                        listEntitiesBackground2.push_back(entity.value());
                        break;
                    case EntityType::Background3:
                        listEntitiesBackground3.push_back(entity.value());
                        break;
                    case EntityType::Player:
                        listEntitiesPlayer.push_back(entity.value());
                        break;
                    case EntityType::Enemy1:
                        listEntitiesEnemy.push_back(entity.value());
                        break;
                    case EntityType::Enemy2:
                        listEntitiesEnemy.push_back(entity.value());
                        break;
                    case EntityType::Boss1:
                        listEntitiesEnemy.push_back(entity.value());
                        break;
                    case EntityType::Bullet:
                        listEntitiesBullet.push_back(entity.value());
                        break;
                    default:
                        break;
                }
            }
        }
        listEntitiesBackground3.insert(listEntitiesBackground3.end(), listEntitiesBackground2.begin(), listEntitiesBackground2.end());
        listEntitiesBackground3.insert(listEntitiesBackground3.end(), listEntitiesBackground1.begin(), listEntitiesBackground1.end());
        listEntitiesBackground3.insert(listEntitiesBackground3.end(), listEntitiesEnemy.begin(), listEntitiesEnemy.end());
        listEntitiesBackground3.insert(listEntitiesBackground3.end(), listEntitiesPlayer.begin(), listEntitiesPlayer.end());
        listEntitiesBackground3.insert(listEntitiesBackground3.end(), listEntitiesBullet.begin(), listEntitiesBullet.end());
        return listEntitiesBackground3;
    }

    int Graph::_displayTexture(ECS::Entity &entity)
    {
        std::shared_ptr<ECS::Sprite> sprite = std::dynamic_pointer_cast<ECS::Sprite>(entity.getComponent(ComponentType::Sprite));

        std::vector<Texture2D> textures;
        for (const auto &anyTexture : sprite->getTexturesToDisplay()) {
            textures.push_back(std::any_cast<Texture2D>(anyTexture));
        }
        Vector2 pos = Vector2({(float)sprite->getPosX(), (float)sprite->getPosY()});
        Vector2 transform = Vector2({(float)sprite->getRotation(), (float)sprite->getScale()});
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
        return std::make_shared<Raylib::RlSprite>();
    }

    std::shared_ptr<ECS::Sprite> createSprite(const int x, const int y)
    {
        return std::make_shared<Raylib::RlSprite>(x, y);
    }

    std::shared_ptr<ECS::Sprite> createSprite(const std::vector<std::string> pathTextures, std::vector<int> textureIndexes)
    {
        return std::make_shared<Raylib::RlSprite>(pathTextures, textureIndexes);
    }

    std::shared_ptr<ECS::Musics> createMusics(const std::string path)
    {
        return std::make_shared<Raylib::RlMusic>(path);
    }

    std::shared_ptr<ECS::Sounds> createSound(const std::string path)
    {
        return std::make_shared<Raylib::RlSound>(path);
    }

    std::shared_ptr<ECS::Weapon> createWeapon(const std::string path)
    {
        return std::make_shared<Raylib::RlWeapon>(path);
    }

    void createWindow(int width, int heigth, std::string name, int frameRate)
    {
        Raylib::initWindow(width, heigth, name, frameRate);
        InitAudioDevice();
    }

    void closeWindow()
    {
        Raylib::closeWindow();
        CloseAudioDevice();
    }

    void refreshWindow()
    {
        Raylib::clear(Color({0, 0, 0, 255}));
    }

    bool checkWindowOpen()
    {
        return !Raylib::windowShouldClose();
    }

    double getDeltaTime()
    {
        return Raylib::getElapsedTime();
    }
} // namespace Graphic
