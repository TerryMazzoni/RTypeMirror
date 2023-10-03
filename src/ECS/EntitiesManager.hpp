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
            std::vector<Entity> getEntities();
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
             * @brief Clear the list of entities and set the size as 5 to prevent boutons
             *
             * @return int
             */
            int clearEntities();
            /**
             * @brief Update the value of a component for a list of entities
             *
             * @param std::any
             * @param ComponentType
             * @param std::vector<Entity>
             * @return int
             */
            int updateEntities(std::any value, ComponentType compoType, std::vector<Entity> entitiesToUpdate);

        protected:
        private:
            void resizeMapComponent();
            void addComponentsEntity(Entity entity);

            std::vector<Entity> _listEntities;
            std::map<ComponentType, std::vector<std::optional<std::shared_ptr<ECS::IComponent>>>> _mapComponent;
            int _sizeListComponents;
    };
} // namespace ECS
