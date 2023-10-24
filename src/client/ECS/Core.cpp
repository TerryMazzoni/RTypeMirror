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
#include "Shoot.hpp"
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

        // for (Parser::entity_t &entityData : entities) {
        //     Entity entity;
        //     std::ostringstream textureostring;
        //     std::copy(entityData.textures.first.begin(), entityData.textures.first.end(), std::ostream_iterator<std::string>(textureostring, ","));
        //     std::copy(entityData.etextures.second.begin(), entityData.textures.second.end(), std::ostream_iterator<int>(textureostring, ","));
        //     std::string textureString = textureostring.str().erase(textureostring.str().size() - 1);

        //     if (entityData.type == "__player__") {
        //         std::shared_ptr<ECS::IComponent> componentT = ECS::Factory::createComponent(ComponentType::Texture, textureString);
        //         componentT->setType(ComponentType::Texture);
        //         entity.components.push_back(componentT);


        //         if (entityData.instance.count("x") == 0 || entityData.instance.count("y") == 0)
        //             throw std::runtime_error("ERROR: entity __player__ have invalid position");
        //         std::shared_ptr<ECS::IComponent> componentP = ECS::Factory::createComponent(ComponentType::Position, (entityData.instance["x"].getString() + "," + entityData.instance["y"].getString()));
        //         componentP->setType(ComponentType::Position);
        //         entity.components.push_back(componentP);

        //         if (entityData.instance.count("scale") == 0)
        //             throw std::runtime_error("ERROR: entity __player__ have invalid scale");
        //         std::shared_ptr<ECS::IComponent> componentS = ECS::Factory::createComponent(ComponentType::Scale, entityData.instance["scale"].getString());
        //         componentS->setType(ComponentType::Scale);
        //         entity.components.push_back(componentS);



        //         entity.id = {EntityType::Player, id};
        //         _eventManager.setMyPlayer(entity);

        //         std::shared_ptr<ISystem> changeTexture = std::make_shared<ChangeTexture>(ChangeTexture());
        //         changeTexture->setEntity(entity);

        //         std::shared_ptr<ISystem> shoot = std::make_shared<Shoot>(Shoot());
        //         shoot->setEntity(entity);
        //          else if (entityData.type == "__tile__") {
        //          std::shared_ptr<ECS::IComponent> componentT = ECS::Factory::createComponent(ComponentType::Texture, textureString);
        //          componentT->setType(ComponentType::Texture);
        //         _systemManager.addSystems({changeTexture, shoot});
        //     }
        //     else if (entityData.type == "__tile__") {
        //         std::shared_ptr<ECS::IComponent> componentT = ECS::Factory::createComponent(ComponentType::Texture, textureString);
        //         componentT->setType(ComponentType::Texture);
        //         entity.components.push_back(componentT);

        //         std::shared_ptr<ECS::IComponent> componentP = ECS::Factory::createComponent(ComponentType::Position, (entityData.instance["x"].getString() + "," + entityData.instance["y"].getString()));
        //         componentP->setType(ComponentType::Position);
        //         entity.components.push_back(componentP);

        //         entity.id = {EntityType::Background, id};
        //     }
        //     id++;
        //     _entitiesManager.addEntities({entity});
        // }
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
        // Entity bullet;

        // std::shared_ptr<ECS::IComponent> texture = ECS::Factory::createComponent(ComponentType::Texture, "assets/bullet/ammu1.png");
        // texture->setType(ComponentType::Texture);
        // bullet.components.push_back(texture);
        // std::shared_ptr<ECS::IComponent> componentP = entity.getComponent(ComponentType::Position);
        // float x = std::any_cast<ECS::Position>(componentP->getValue()).x;
        // float y = std::any_cast<ECS::Position>(componentP->getValue()).y;
        // std::shared_ptr<ECS::IComponent> position = ECS::Factory::createComponent(ComponentType::Position, std::to_string(x + 64 * 3) + "," + std::to_string(y + 32 * 3));
        // position->setType(ComponentType::Position);
        // bullet.components.push_back(position);
        // bullet.id = {EntityType::Bullet, _entitiesManager.getEntities().size()};

        // std::shared_ptr<ISystem> bulletMouvement = std::make_shared<BulletMouvement>(BulletMouvement());
        // bulletMouvement->setEntity(bullet);
        // _entitiesManager.addEntities({bullet});
        // _systemManager.addSystems({bulletMouvement});
    }
} // namespace ECS
