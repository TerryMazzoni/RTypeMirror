/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Core
*/

#include <iostream>
#include "Core.hpp"
#include "Mouvement.hpp"

namespace ECS {

    Core::Core()
    {
        _entitiesManager = EntitiesManager();
        _eventManager = EventManager();
        _systemManager = SystemManager();

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

        Entity entity2;
        std::shared_ptr<ECS::IComponent> component2T = ECS::Factory::createComponent(ComponentType::Texture, "assets/spaceship/sprite_spaceships0.png");
        component2T->setType(ComponentType::Texture);
        entity2.components.push_back(component2T);
        std::shared_ptr<ECS::IComponent> component2P = ECS::Factory::createComponent(ComponentType::Position, "300,100");
        component2P->setType(ComponentType::Position);
        entity2.components.push_back(component2P);
        entity2.id = {EntityType::Player, 1};
        std::shared_ptr<ISystem> mouvement = std::make_shared<Mouvement>(Mouvement());
        mouvement->setEntity(entity2);

        _systemManager.addSystems({mouvement});
        _entitiesManager.addEntities({entity, entity2});
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
            _entitiesManager.updateEntities(_systemManager.execute());
            Raylib::beginDraw();
            inputs = Raylib::getInputs();
            _graph.displayEntities(_entitiesManager.getEntities());
            Raylib::endDraw();
        }
        return 0;
    }
} // namespace ECS
