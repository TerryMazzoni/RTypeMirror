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
#include "ChangeTexture.hpp"
#include "Parser.hpp"
#include "Graph.hpp"
#include "TransformPath.hpp"

namespace ECS {
    Core::Core()
    {
        _entitiesManager = EntitiesManager();
        _eventManager = EventManager();
        _systemManager = SystemManager();
        _graph = Graphic::Graph();
    }

    Core::~Core()
    {
        Graphic::closeWindow();
    }

    void Core::initWindow()
    {
        if (!Graphic::checkWindowOpen()) {
            Graphic::createWindow(1920, 1080, "RTypeMirror", 60);
        }
    }

    void Core::init(int id)
    {
        std::vector<Parser::entity_t> entities;

        try {
            entities = Parser::ParserJson(transformPath(std::string("assets/map.json"))).parse().getEntities();
        }
        catch (Parser::ParserException &e) {
            throw std::runtime_error(e.what());
        }
        Entity background;
        std::shared_ptr<ECS::IComponent> componentBT = ECS::Factory::createComponent(ComponentType::Sprite, "assets/background/road1.png");
        componentBT->setType(ComponentType::Sprite);
        background.components.push_back(componentBT);
        background.id = {EntityType::Background, 5};

        _entitiesManager.addEntities({background});

        int index = 1;
        for (Parser::entity_t &entityData : entities) {
            Entity entity;
            std::ostringstream textureostring;
            std::copy(entityData.textures.first.begin(), entityData.textures.first.end(), std::ostream_iterator<std::string>(textureostring, ","));
            std::copy(entityData.textures.second.begin(), entityData.textures.second.end(), std::ostream_iterator<int>(textureostring, ","));
            std::string textureString = textureostring.str().erase(textureostring.str().size() - 1);

            if (entityData.type == "__player__" && index == id) {
                std::cout << "Player index :" << index << std::endl;
                std::shared_ptr<ECS::Sprite> sprite = std::dynamic_pointer_cast<ECS::Sprite>(ECS::Factory::createComponent(ComponentType::Sprite, textureString));
                if (entityData.instance.count("x") == 0 || entityData.instance.count("y") == 0) {
                    throw std::runtime_error("ERROR: entity __player__ have invalid position");
                }
                sprite->setPosition(std::make_pair(entityData.instance["x"].getInt(), entityData.instance["y"].getInt()));
                if (entityData.instance.count("scale") == 0) {
                    throw std::runtime_error("ERROR: entity __player__ have invalid scale");
                }
                if (entityData.instance.count("speed") == 0)
                    throw std::runtime_error("ERROR: entity __player__ have invalid speed");
                sprite->setScale(entityData.instance["scale"].getFloat());
                sprite->setType(ComponentType::Sprite);
                sprite->setSpeed(entityData.instance["speed"].getFloat());
                entity.components.push_back(sprite);

                entity.id = {EntityType::Player, index};
                _eventManager.setMyPlayer(entity);

                std::shared_ptr<ISystem> changeTexture = std::make_shared<ChangeTexture>(ChangeTexture());
                changeTexture->setEntity(entity);

                _systemManager.addSystems({changeTexture});
                if (index == id)
                    _eventManager.setMyPlayer(entity);
            }
            else if (entityData.type == "__tile__") {
                std::shared_ptr<ECS::Sprite> sprite = std::dynamic_pointer_cast<ECS::Sprite>(ECS::Factory::createComponent(ComponentType::Sprite, textureString));
                if (entityData.instance.count("x") == 0 || entityData.instance.count("y") == 0) {
                    throw std::runtime_error("ERROR: entity __player__ have invalid position");
                }
                sprite->setPosition(std::make_pair(entityData.instance["x"].getInt(), entityData.instance["y"].getInt()));

                sprite->setType(ComponentType::Sprite);
                entity.components.push_back(sprite);

                entity.id = {EntityType::Background, index};
            }
            index++;
            _entitiesManager.addEntities({entity});
        }
    }

    int Core::run(std::shared_ptr<Client> client)
    {
        Communication::Quit quit;
        Communication::Ready ready;
        std::set<Input> inputs;

        while (client->getId() == 0)
            ;
        initWindow();
        init(client->getId());
        while (Graphic::checkWindowOpen() and is_running(0)) {
            Graphic::refreshWindow();
            _eventManager.executeInputs(inputs);
            std::vector<Entity> entitiesToDelete = _entitiesManager.getEntitiesToDelete();
            _entitiesManager.removeEntities(entitiesToDelete);
            _systemManager.removeSystems(entitiesToDelete);
            executeServerActions(client->getShipsPositions());
            executeServerActions(client->getMissilesPositions());
            _entitiesManager.updateEntities(_eventManager.getActions());
            _eventManager.clear();
            _entitiesManager.updateEntities(_systemManager.execute());
            _createEntities();
            _entitiesManager.clearEntitiesToCreate();
            inputs = _graph.getInputs();
            client->setEvents(transformInputsForClient(inputs));
            _graph.displayEntities(_entitiesManager.getEntities());
        }
        is_running(1);
        client->send(quit);
        return 0;
    }

    int Core::executeServerActions(std::vector<Communication::ShipsPosition> ships)
    {
        for (auto &ship : ships)
            _eventManager.executeServerActions(ship);
        return 0;
    }

    int Core::executeServerActions(std::vector<Communication::MissilesPosition> missiles)
    {
        for (auto &missile : missiles)
            _eventManager.executeServerActions(missile);
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

    void Core::_createEntities()
    {
        std::vector<std::pair<std::vector<Entity>, EntityType>> entities = _entitiesManager.getEntitiesToCreate();

        for (auto &entity : entities) {
            switch (entity.second) {
                case EntityType::Bullet:
                    for (Entity entity : entity.first) {
                        _createBullet(entity);
                    }
                    break;
                case EntityType::Player:
                    for (Entity entity : entity.first) {
                        _createPlayer(entity);
                    }
                default:
                    break;
            }
        }
    }

    void Core::_createBullet(Entity entity)
    {
        Entity bullet;

        std::shared_ptr<ECS::Sprite> sprite = std::dynamic_pointer_cast<ECS::Sprite>(ECS::Factory::createComponent(ComponentType::Sprite, "assets/bullet/ammu1.png"));
        sprite->setType(ComponentType::Sprite);
        std::shared_ptr<ECS::Sprite> spriteToCopy = std::dynamic_pointer_cast<ECS::Sprite>(entity.getComponent(ComponentType::Sprite));
        sprite->setPosition(spriteToCopy->getPos());
        bullet.components.push_back(sprite);
        bullet.id = {EntityType::Bullet, entity.id.second};

        std::shared_ptr<ISystem> bulletMouvement = std::make_shared<BulletMouvement>();
        bulletMouvement->setEntity(bullet);
        _entitiesManager.addEntities({bullet});
        // _systemManager.addSystems({bulletMouvement});
    }

    void Core::_createPlayer(Entity entity)
    {
        Entity player;

        std::shared_ptr<ECS::Sprite> sprite = std::dynamic_pointer_cast<ECS::Sprite>(ECS::Factory::createComponent(ComponentType::Sprite, PATH_TEXTURES_PLAYER));
        sprite->setType(ComponentType::Sprite);
        std::shared_ptr<ECS::Sprite> spriteToCopy = std::dynamic_pointer_cast<ECS::Sprite>(entity.getComponent(ComponentType::Sprite));
        sprite->setPosition(spriteToCopy->getPos());
        sprite->setScale(3);
        player.components.push_back(sprite);
        player.id = {EntityType::Player, entity.id.second};

        std::shared_ptr<ISystem> textureChange = std::make_shared<ChangeTexture>();
        textureChange->setEntity(player);
        std::cout << "Create player: " << player.id.second << std::endl;
        _entitiesManager.addEntities({player});
        _systemManager.addSystems({textureChange});
    }
} // namespace ECS
