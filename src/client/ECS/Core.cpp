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
#include "UpdateMusic.hpp"
#include "UpdatePosGun.hpp"
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
        if (Graphic::checkWindowOpen())
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
        background.id = {EntityType::Background3, 5};

        _entitiesManager.addEntities({background});

        int index = 1;
        for (Parser::entity_t &entityData : entities) {
            Entity entity;
            std::ostringstream textureostring;
            std::copy(entityData.textures.first.begin(), entityData.textures.first.end(), std::ostream_iterator<std::string>(textureostring, ","));
            std::copy(entityData.textures.second.begin(), entityData.textures.second.end(), std::ostream_iterator<int>(textureostring, ","));
            std::string textureString = textureostring.str().erase(textureostring.str().size() - 1);

            if (entityData.type == "__player__" && index == id) {
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

                std::shared_ptr<ECS::Weapon> weapon = std::dynamic_pointer_cast<ECS::Weapon>(ECS::Factory::createComponent(ComponentType::Weapon, "assets/gun/gun1.png"));
                weapon->setType(ComponentType::Weapon);
                std::dynamic_pointer_cast<ECS::Sprite>(weapon->getSprite())->setPosition(std::make_pair(entityData.instance["x"].getInt(), entityData.instance["y"].getInt()));
                std::dynamic_pointer_cast<ECS::Sprite>(weapon->getSprite())->setScale(entityData.instance["scale"].getFloat());
                entity.components.push_back(weapon);

                entity.id = {EntityType::Player, index};
                _eventManager.setMyPlayer(entity);

                if (index == id) {
                    std::shared_ptr<ECS::Musics> music = std::dynamic_pointer_cast<ECS::Musics>(ECS::Factory::createComponent(ComponentType::Music, "assets/music/game_theme.ogg"));
                    music->setType(ComponentType::Music);
                    music->play();
                    entity.components.push_back(music);
                    std::shared_ptr<ISystem> updateMusic = std::make_shared<UpdateMusic>();
                    updateMusic->setEntity(entity);
                    _eventManager.setMyPlayer(entity);
                    _systemManager.addSystems({updateMusic});
                    switch (id) {
                        case 1:
                            sprite->setColor(255, 0, 0, 255, {1, 2});
                            break;
                        case 2:
                            sprite->setColor(0, 0, 255, 255, {1, 2});
                            break;
                        case 3:
                            sprite->setColor(0, 255, 0, 255, {1, 2});
                            break;
                        case 4:
                            sprite->setColor(0, 255, 255, 255, {1, 2});
                            break;
                        default:
                            break;
                    }
                }
                std::shared_ptr<ISystem> changeTexture = std::make_shared<ChangeTexture>(ChangeTexture());
                changeTexture->setEntity(entity);

                std::shared_ptr<ISystem> updatePosGun = std::make_shared<UpdatePosGun>();
                updatePosGun->setEntity(entity);

                _systemManager.addSystems({changeTexture, updatePosGun});
            }
            else if (entityData.type == "__tile__") {
                std::shared_ptr<ECS::Sprite> sprite = std::dynamic_pointer_cast<ECS::Sprite>(ECS::Factory::createComponent(ComponentType::Sprite, textureString));
                if (entityData.instance.count("x") == 0 || entityData.instance.count("y") == 0) {
                    throw std::runtime_error("ERROR: entity __player__ have invalid position");
                }
                sprite->setPosition(std::make_pair(entityData.instance["x"].getInt(), entityData.instance["y"].getInt()));

                sprite->setType(ComponentType::Sprite);
                entity.components.push_back(sprite);

                entity.id = {EntityType::Background1, index};
            }
            index++;
            _entitiesManager.addEntities({entity});
        }
        Entity entityReady;
        std::shared_ptr<ECS::IComponent> ready = ECS::Factory::createComponent(ComponentType::Sprite, "assets/READY.png");
        std::dynamic_pointer_cast<ECS::Sprite>(ready)->setPosition(std::make_pair(500, 800));
        std::dynamic_pointer_cast<ECS::Sprite>(ready)->setScale(2);
        ready->setType(ComponentType::Sprite);
        entityReady.components.push_back(ready);
        entityReady.id.first = EntityType::Background1;
        entityReady.id.second = _entitiesManager.getEntities().size();
        _entitiesManager.addEntities({entityReady});
    }

    int Core::run(std::shared_ptr<Client> client)
    {
        Communication::Quit quit;
        Communication::Ready ready;
        std::set<Input> inputs;

        while (client->getId() == 0)
            if (!is_running(0))
                return 1;
        initWindow();
        init(client->getId());
        while (Graphic::checkWindowOpen() and is_running(0)) {
            if (!client->getIsReady())
                client->setIsReady(_eventManager.getClientReady());
            setDeltaTime();
            Graphic::refreshWindow();
            _eventManager.executeInputs(inputs);
            std::vector<Entity> entitiesToDelete = _entitiesManager.getEntitiesToDelete();
            _entitiesManager.removeEntities(entitiesToDelete);
            _entitiesManager.removeEntities(client->getEntitiesToDelete());
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
                        _createShip(entity);
                    }
                    break;
                case EntityType::Enemy1:
                    for (Entity entity : entity.first) {
                        _createShip(entity);
                    }
                    break;
                case EntityType::Enemy2:
                    for (Entity entity : entity.first) {
                        _createShip(entity);
                    }
                    break;
                case EntityType::Boss1:
                    for (Entity entity : entity.first) {
                        _createShip(entity);
                    }
                    break;
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

        _entitiesManager.addEntities({bullet});
    }

    void Core::_createShip(Entity entity)
    {
        Entity ship;
        std::string path;

        switch (entity.id.first) {
            case (EntityType::Player):
                path = PATH_TEXTURES_PLAYER;
                break;
            case (EntityType::Enemy1):
                path = PATH_TEXTURES_ENEMY1;
                break;
            case (EntityType::Enemy2):
                path = PATH_TEXTURES_ENEMY2;
                break;
            case (EntityType::Boss1):
                path = PATH_TEXTURES_BOSS1;
                break;
            default:
                break;
        }
        std::shared_ptr<ECS::Sprite> sprite = std::dynamic_pointer_cast<ECS::Sprite>(ECS::Factory::createComponent(ComponentType::Sprite, path));
        sprite->setType(ComponentType::Sprite);
        std::shared_ptr<ECS::Sprite> spriteToCopy = std::dynamic_pointer_cast<ECS::Sprite>(entity.getComponent(ComponentType::Sprite));
        sprite->setPosition(spriteToCopy->getPos());
        sprite->setScale(spriteToCopy->getScale());
        ship.components.push_back(sprite);
        ship.id = {EntityType::Player, entity.id.second};

        std::shared_ptr<ISystem> textureChange = std::make_shared<ChangeTexture>();
        textureChange->setEntity(ship);
        if (entity.id.first == EntityType::Player) {
            std::shared_ptr<ECS::Weapon> weapon = std::dynamic_pointer_cast<ECS::Weapon>(ECS::Factory::createComponent(ComponentType::Weapon, "assets/gun/gun1.png"));
            weapon->setType(ComponentType::Weapon);
            std::dynamic_pointer_cast<ECS::Sprite>(weapon->getSprite())->setPosition(sprite->getPos());
            std::dynamic_pointer_cast<ECS::Sprite>(weapon->getSprite())->setScale(sprite->getScale());
            ship.components.push_back(weapon);

            std::shared_ptr<ISystem> updatePosGun = std::make_shared<UpdatePosGun>();
            updatePosGun->setEntity(ship);
            _systemManager.addSystems({updatePosGun});
        }
        _entitiesManager.addEntities({ship});
        _systemManager.addSystems({textureChange});
    }

    void Core::setDeltaTime()
    {
        double deltaTime = Graphic::getDeltaTime();

        _entitiesManager.setDeltaTime(deltaTime);
        _eventManager.setDeltaTime(deltaTime);
    }
} // namespace ECS
