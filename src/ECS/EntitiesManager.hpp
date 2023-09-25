/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** EntitiesManager
*/

#ifndef ENTITIESMANAGER_HPP_
#define ENTITIESMANAGER_HPP_

#include <vector>
#include "Enum.hpp"

namespace ECS {
    class EntitiesManager {
        public:
            EntitiesManager();
            ~EntitiesManager();
            std::vector<Entity> getEntities(SceneType scene);
            int addEntities(SceneType scene, std::vector<Entity> entitiesToAdd);
            int removeEntities(SceneType scene, std::vector<Entity> entitiesToRemove);
            template <typename T>
            int updateEntities(T value, std::vector<Entity> entitiesToUpdate);

        protected:
        private:
            std::vector<Entity> _listEntities;
    };
} // namespace ECS

#endif /* !ENTITIESMANAGER_HPP_ */
