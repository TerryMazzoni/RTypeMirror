/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Core
*/

#include <iostream>
#include "Core.hpp"
#include "BulletMouvement.hpp"
#include "Mouvement.hpp"
#include "Shoot.hpp"
#include "ChangeTexture.hpp"

namespace ECS {

    Core::Core()
    {
        _entitiesManager = EntitiesManager();
        _eventManager = EventManager();
        _systemManager = SystemManager();

        Raylib::initWindow(1920, 1080, "RTypeMirror", 60);

        Entity background;
        std::shared_ptr<ECS::IComponent> componentBT = ECS::Factory::createComponent(ComponentType::Texture, "assets/starfield.png");
        componentBT->setType(ComponentType::Texture);
        background.components.push_back(componentBT);
        std::shared_ptr<ECS::IComponent> componentBP = ECS::Factory::createComponent(ComponentType::Position, "0,0");
        componentBP->setType(ComponentType::Position);
        background.components.push_back(componentBP);
        background.id = {EntityType::Background, 2};

        Entity entity;
        std::shared_ptr<ECS::IComponent> componentT = ECS::Factory::createComponent(ComponentType::Texture, "assets/spaceship/sprite_spaceships0.png,assets/spaceship/sprite_spaceships1.png,assets/spaceship/sprite_spaceships2.png,assets/spaceship/sprite_spaceships3.png,assets/capsule/sprite_capsules0.png,assets/capsule/sprite_capsules1.png,assets/capsule/sprite_capsules2.png,assets/capsule/sprite_capsules3.png,0,4");
        componentT->setType(ComponentType::Texture);
        entity.components.push_back(componentT);
        std::shared_ptr<ECS::IComponent> componentP = ECS::Factory::createComponent(ComponentType::Position, "300,100");
        componentP->setType(ComponentType::Position);
        entity.components.push_back(componentP);
        std::shared_ptr<ECS::IComponent> componentS = ECS::Factory::createComponent(ComponentType::Scale, "3");
        componentS->setType(ComponentType::Scale);
        entity.components.push_back(componentS);
        entity.id = {EntityType::Player, 0};
        _eventManager.setMyPlayer(entity);
        std::shared_ptr<ISystem> changeTexture = std::make_shared<ChangeTexture>(ChangeTexture());
        changeTexture->setEntity(entity);
        std::shared_ptr<ISystem> shoot = std::make_shared<Shoot>(Shoot());
        shoot->setEntity(entity);

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

        _systemManager.addSystems({mouvement, changeTexture, shoot});
        _entitiesManager.addEntities({background, entity, entity2});
    }

    Core::~Core()
    {
        Raylib::closeWindow();
    }

    int Core::run(std::shared_ptr<Client> client)
    {
        Communication::Quit quit;
        std::set<Input> inputs;

        while (!Raylib::windowShouldClose() and is_running(0)) {
            Raylib::clear(Raylib::RlColor(0, 0, 0));
            _eventManager.executeInputs(inputs);
            std::vector<Entity> entitiesToDelete = _entitiesManager.getEntitiesToDelete();
            _entitiesManager.removeEntities(entitiesToDelete);
            _systemManager.removeSystems(entitiesToDelete);
            _entitiesManager.updateEntities(_eventManager.getActions());
            _entitiesManager.updateEntities(_systemManager.execute());
            createEntities();
            Raylib::beginDraw();
            inputs = Raylib::getInputs();
            client->setEvents(transformInputsForClient(inputs));
            _graph.displayEntities(_entitiesManager.getEntities());
            Raylib::endDraw();
        }
        is_running(1);
        client->send(quit);
        return 0;
    }

    std::vector<EventInput> Core::transformInputsForClient(std::set<Input> inputs)
    {
        std::vector<EventInput> eventInputs;

        for (auto input : inputs)
        {
            eventInputs.push_back((EventInput)std::get<1>(input));
        }
        return eventInputs;
    }

    void Core::createEntities()
    {
        std::vector<std::pair<std::vector<Entity>, EntityType>> entities = _entitiesManager.getEntitiesToCreate();

        for (auto &entities : entities) {
            switch (entities.second) {
                case EntityType::Bullet:
                    for (Entity entity : entities.first) {
                        createBullet(entity);
                    }
                    break;
                default:
                    break;
            }
        }
    }

    void Core::createBullet(Entity entity)
    {
        Entity bullet;

        std::shared_ptr<ECS::IComponent> texture = ECS::Factory::createComponent(ComponentType::Texture, "assets/bullet/ammu1.png");
        texture->setType(ComponentType::Texture);
        bullet.components.push_back(texture);
        std::shared_ptr<ECS::IComponent> componentP = entity.getComponent(ComponentType::Position);
        float x = std::any_cast<ECS::Position>(componentP->getValue()).x;
        float y = std::any_cast<ECS::Position>(componentP->getValue()).y;
        std::shared_ptr<ECS::IComponent> position = ECS::Factory::createComponent(ComponentType::Position, std::to_string(x + 64 * 3) + "," + std::to_string(y + 32 * 3));
        position->setType(ComponentType::Position);
        bullet.components.push_back(position);
        bullet.id = {EntityType::Bullet, _entitiesManager.getEntities().size()};

        std::shared_ptr<ISystem> bulletMouvement = std::make_shared<BulletMouvement>(BulletMouvement());
        bulletMouvement->setEntity(bullet);

        _entitiesManager.addEntities({bullet});
        _systemManager.addSystems({bulletMouvement});
    }
} // namespace ECS
