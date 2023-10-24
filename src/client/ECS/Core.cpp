/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Core
*/

#include <iostream>
#include <vector>
#include "Core.hpp"
#include "BulletMouvement.hpp"
#include "Mouvement.hpp"
#include "ChangeTexture.hpp"
#include "Parser.hpp"
#include "Graph.hpp"

namespace ECS
{
    Core::Core()
    {
        _id = 1;
        std::vector<Parser::entity_t> entities;

        try {
            entities = Parser::ParserJson("assets/test.json").parse().getEntities();
        }
        catch (Parser::ParserException &e) {
            throw std::runtime_error(e.what());
        }
        _entitiesManager = EntitiesManager();
        _eventManager = EventManager();
        _systemManager = SystemManager();
        _graph = Graphic::Graph();
        Graphic::createWindow(1920, 1080, "RTypeMirror", 60);

        std::cout << "parse" << std::endl;
        Entity background;
        std::shared_ptr<ECS::IComponent> componentBT = ECS::Factory::createComponent(ComponentType::Sprite, "assets/background/road1.png");
        componentBT->setType(ComponentType::Sprite);
        background.components.push_back(componentBT);
        background.id = {EntityType::Background, 5};

        _entitiesManager.addEntities({background});

        for (Parser::entity_t &entityData : entities) {
            Entity entity;
            std::ostringstream textureostring;
            std::copy(entityData.textures.first.begin(), entityData.textures.first.end(), std::ostream_iterator<std::string>(textureostring, ","));
            std::copy(entityData.textures.second.begin(), entityData.textures.second.end(), std::ostream_iterator<int>(textureostring, ","));
            std::string textureString = textureostring.str().erase(textureostring.str().size() - 1);

            if (entityData.type == "__player__") {

                std::shared_ptr<ECS::Sprite> sprite = std::dynamic_pointer_cast<ECS::Sprite>(ECS::Factory::createComponent(ComponentType::Sprite, textureString));
                if (entityData.instance.count("x") == 0 || entityData.instance.count("y") == 0)
                    throw std::runtime_error("ERROR: entity __player__ have invalid position");
                sprite->setPosition(std::make_pair(entityData.instance["x"].getInt(), entityData.instance["y"].getInt()));
                if (entityData.instance.count("scale") == 0)
                    throw std::runtime_error("ERROR: entity __player__ have invalid scale");
                sprite->setScale(entityData.instance["scale"].getFloat());
                sprite->setScale(3);
                sprite->setType(ComponentType::Sprite);
                entity.components.push_back(sprite);

                entity.id = {EntityType::Player, _id};
                _eventManager.setMyPlayer(entity);

                std::shared_ptr<ISystem> changeTexture = std::make_shared<ChangeTexture>(ChangeTexture());
                changeTexture->setEntity(entity);

                _systemManager.addSystems({changeTexture});
            }
            else if (entityData.type == "__tile__") {
                std::shared_ptr<ECS::Sprite> sprite = std::dynamic_pointer_cast<ECS::Sprite>(ECS::Factory::createComponent(ComponentType::Sprite, textureString));
                if (entityData.instance.count("x") == 0 || entityData.instance.count("y") == 0)
                    throw std::runtime_error("ERROR: entity __player__ have invalid position");
                sprite->setPosition(std::make_pair(entityData.instance["x"].getInt(), entityData.instance["y"].getInt()));

                sprite->setType(ComponentType::Sprite);
                entity.components.push_back(sprite);

                entity.id = {EntityType::Background, _id};
            }
            _id++;
            _entitiesManager.addEntities({entity});
        }
    }

    Core::~Core()
    {
        Graphic::closeWindow();
    }

    void Core::init(int id)
    {
        _eventManager.updateMyPlayer(id);
    }

    int Core::run(std::shared_ptr<Client> client)
    {
        Communication::Quit quit;
        std::set<Input> inputs;

        while (Graphic::checkWindowOpen() and is_running(0)) {
            Graphic::refreshWindow();
            _eventManager.executeInputs(inputs);
            std::vector<Entity> entitiesToDelete = _entitiesManager.getEntitiesToDelete();
            _entitiesManager.removeEntities(entitiesToDelete);
            _systemManager.removeSystems(entitiesToDelete);
            _entitiesManager.updateEntities(_eventManager.getActions());
            _eventManager.clear();
            _entitiesManager.updateEntities(_systemManager.execute());
            createEntities();
            inputs = _graph.getInputs();
            client->setEvents(transformInputsForClient(inputs));
            _graph.displayEntities(_entitiesManager.getEntities());
        }
        is_running(1);
        client->send(quit);
        return 0;
    }

    int Core::executeServerActions(Communication::ShipsPosition ships)
    {
        _eventManager.executeServerActions(ships);
        return 0;
    }

    int Core::executeServerActions(Communication::MissilesPosition missiles)
    {
        _eventManager.executeServerActions(missiles);
        return 0;
    }

    std::vector<EventInput> Core::transformInputsForClient(std::set<Input> inputs)
    {
        std::vector<EventInput> eventInputs;

        for (auto input : inputs) {
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

        std::shared_ptr<ECS::Sprite> sprite = std::dynamic_pointer_cast<ECS::Sprite>(ECS::Factory::createComponent(ComponentType::Sprite, "assets/bullet/ammu1.png"));
        sprite->setType(ComponentType::Sprite);
        std::shared_ptr<ECS::Sprite> spriteToCopy = std::dynamic_pointer_cast<ECS::Sprite>(entity.getComponent(ComponentType::Sprite));
        sprite->setPosition(spriteToCopy->getPos());
        bullet.components.push_back(sprite);
        bullet.id = {EntityType::Bullet, entity.id.second};

        std::shared_ptr<ISystem> bulletMouvement = std::make_shared<BulletMouvement>(BulletMouvement());
        bulletMouvement->setEntity(bullet);
        _entitiesManager.addEntities({bullet});
        _systemManager.addSystems({bulletMouvement});
    }
} // namespace ECS
