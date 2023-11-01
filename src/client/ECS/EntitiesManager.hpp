/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** EntitiesManager
*/

#pragma once

#include <vector>
#include <optional>
#include <map>
#include <string>
#include "Enum.hpp"
#include "Component.hpp"
#include "Entity.hpp"

namespace ECS {
    class EntitiesManager {
        public:
            EntitiesManager();
            ~EntitiesManager();
            /**
             * @brief Get the list of entities
             *
             * @return std::vector<Entity>
             */
            std::vector<std::optional<Entity>> getEntities();
            /**
             * @brief Add a list of entities in the entity manager
             *
             * @param std::vector<Entity>
             * @return int
             */
            int addEntities(std::vector<Entity> entitiesToAdd);
            /**
             * @brief Remove a list of entities in the entity manager
             *
             * @param std::vector<Entity>
             * @return int
             */
            int removeEntities(std::vector<Entity> entitiesToRemove);
            /**
             * @brief Remove a list of entities in the entity manager
             *
             * @param std::vector<int>
             * @return int
             */
            int removeEntities(std::vector<int> entitiesToRemove);
            /**
             * @brief Clear the list of entities and set the size as 5 to prevent boutons
             *
             * @return int
             */
            int clearEntities();
            /**
             * @brief Update the value of Entity components based on the actions list
             *
             * @param std::vector<Action>
             * @return int
             */
            int updateEntities(std::vector<Action>);
            /**
             * @brief Get the Entities To Create
             *
             * @return std::vector<EntityType>
             */
            std::vector<std::pair<std::vector<Entity>, EntityType>> getEntitiesToCreate();
            /**
             * @brief Get the Entities To be Deleted
             *
             * @return std::vector<int>
             */
            std::vector<Entity> getEntitiesToDelete();
            /**
             * @brief Clear the Entities in the to create vector
             * 
             */
            void clearEntitiesToCreate();
            /**
             * @brief Set the Delta Time object
             * 
             * @param deltaTime 
             */
            void setDeltaTime(double deltaTime);
        protected:
        private:
            void resizeMapComponent();
            void addComponentsEntity(Entity entity);

            std::vector<std::optional<Entity>> _listEntities;
            std::map<ComponentType, std::vector<std::optional<std::shared_ptr<ECS::IComponent>>>> _mapComponent;
            std::vector<std::pair<std::vector<Entity>, EntityType>> _entitiesToCreate;
            std::vector<Entity> _entitiesToDelete;
            int _sizeListComponents;
            double _deltaTime;
    };
} // namespace ECS
