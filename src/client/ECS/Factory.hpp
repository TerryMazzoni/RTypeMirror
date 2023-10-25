/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Factory
*/

#pragma once

#include <vector>
#include <map>
#include <memory>
#include <optional>

#include "IComponent.hpp"
#include "Entity.hpp"

namespace ECS {
    class Factory {
        public:
            Factory(const Factory &) = delete;
            Factory &operator=(const Factory &) = delete;

            /**
             * @brief Create a component
             *
             * @param ComponentType type of the component
             * @param std::string& value of the component
             * @return std::shared_ptr<IComponent>
             */
            static std::shared_ptr<IComponent> createComponent(ComponentType type, const std::string &value);

        private:
            Factory();

            /**
             * @brief Create a Sprite object
             * 
             * @return std::shared_ptr<IComponent> 
             */
            std::shared_ptr<IComponent> createSprite(const std::string &value);
    };
} // namespace ECS