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
        std::shared_ptr<ECS::IComponent> componentT = ECS::Factory::createComponent(ComponentType::Texture, "assets/spaceship/sprite_spaceships0.png");
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
        std::set<Input> inputs;
        while (!Raylib::windowShouldClose()) {
            Raylib::clear(Raylib::RlColor(0, 0, 0));
            _eventManager.executeInputs(inputs);
            _entitiesManager.updateEntities(_eventManager.getActions());
            Raylib::beginDraw();
            inputs = Raylib::getInputs();
            _graph.displayEntities(_entitiesManager.getEntities());
            Raylib::endDraw();
        }
        return 0;
    }
} // namespace ECS
