/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Core
*/

#include <iostream>
#include "Core.hpp"

namespace ECS {

    Core::Core()
    {
        _entitiesManager = EntitiesManager();
        _eventManager = EventManager();

        Raylib::initWindow(1920, 1080, "RTypeMirror", 60);

        Entity entity;
        std::shared_ptr<ECS::IComponent> componentT = ECS::Factory::createComponent(ComponentType::Texture, "src/space.png");
        componentT->setType(ComponentType::Texture);
        entity.components.push_back(componentT);
        std::shared_ptr<ECS::IComponent> componentP = ECS::Factory::createComponent(ComponentType::Position, "300,100");
        componentP->setType(ComponentType::Position);
        entity.components.push_back(componentP);
        entity.id = {EntityType::Player, 0};
        _eventManager.setMyPlayer(entity);

        _entitiesManager.addEntities({entity});
    }

    Core::~Core()
    {
        Raylib::closeWindow();
    }

    int Core::run()
    {
        std::vector<Input> inputs;
        while (!Raylib::windowShouldClose()) {
            Raylib::clear(Raylib::RlColor(0, 0, 0));
            _eventManager.executeInputs(inputs);
            for (auto &action : _eventManager.getActions()) {
                if (std::get<1>(action) == ActionType::Move) {
                    std::shared_ptr<ECS::IComponent> componentP = std::get<0>(action).getComponent(ComponentType::Position);
                    float x = std::any_cast<ECS::Position>(componentP->getValue()).x;
                    float y = std::any_cast<ECS::Position>(componentP->getValue()).y;
                    std::pair<int, int> mouv = std::any_cast<std::pair<int, int>>(std::get<2>(action));
                    _entitiesManager.updateEntities(Position(std::make_pair(x + mouv.first, y + mouv.second)), ComponentType::Position, {std::get<0>(action)});
                }
            }
            Raylib::beginDraw();
            inputs = Raylib::getInputs();
            for (auto &entity : _entitiesManager.getEntities()) {
                std::shared_ptr<ECS::IComponent> componentT = entity.getComponent(ComponentType::Texture);
                std::shared_ptr<ECS::IComponent> componentP = entity.getComponent(ComponentType::Position);
                float x = std::any_cast<ECS::Position>(componentP->getValue()).x;
                float y = std::any_cast<ECS::Position>(componentP->getValue()).y;
                if (componentT != nullptr) {
                    Raylib::draw((std::any_cast<ECS::Texture>(componentT->getValue())).texture, x, y, Raylib::RlColor(255, 255, 255));
                }
            }
            Raylib::endDraw();
        }
        return 0;
    }
} // namespace ECS
