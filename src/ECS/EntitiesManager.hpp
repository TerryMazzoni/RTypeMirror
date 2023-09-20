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
    template <typename T>
    class EntitiesManager {
        public:
            EntitiesManager();
            ~EntitiesManager();
            int updateEntities(T value, EntityType type, int id);
            std::vector<std::pair<EntityType, int>> getEntities(std::string idScene);

        protected:
        private:
            std::vector<std::pair<EntityType, int>> _listEntities;
    };
} // namespace ECS

#endif /* !ENTITIESMANAGER_HPP_ */
