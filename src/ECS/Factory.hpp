/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Factory
*/

#pragma once

#include <vector>
#include <memory>
#include <optional>

#include "IComponent.hpp"
#include "Entity.hpp"

namespace ECS
{
    class Factory
    {
    public:
        Factory(const Factory &) = delete;
        Factory &operator=(const Factory &) = delete;

        static std::optional<Entity> createEntity(ComponentType type, const std::string &value);

    private:
        Factory();

        Entity createEntity(const std::string &value);

        std::vector<std::shared_ptr<ECS::IComponent<std::any>>> _components;

        void createColor(const std::string &value);
        void createPosition(const std::string &value);
        void createRotation(const std::string &value);
        void createScale(const std::string &value);
        void createText(const std::string &value);
        void createTexture(const std::string &value);
    };
}