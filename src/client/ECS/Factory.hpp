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
             * @param type type of the component
             * @param value value of the component
             * @return std::shared_ptr<IComponent>
             */
            static std::shared_ptr<IComponent> createComponent(ComponentType type, const std::string &value);

        private:
            Factory();

            std::shared_ptr<IComponent> createColor(const std::string &value);
            std::shared_ptr<IComponent> createPosition(const std::string &value);
            std::shared_ptr<IComponent> createRotation(const std::string &value);
            std::shared_ptr<IComponent> createScale(const std::string &value);
            std::shared_ptr<IComponent> createText(const std::string &value);
            std::shared_ptr<IComponent> createTexture(const std::string &value);
    };
} // namespace ECS