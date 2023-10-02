/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** IComponent
*/

#pragma once

#include <vector>
#include <any>
#include <string>

#include "Enum.hpp"

namespace ECS
{
    class IComponent
    {
    public:
        virtual ~IComponent() = default;

        virtual int setValue(std::any value) = 0;
        virtual std::any getValue() const = 0;
        virtual ComponentType getType() const = 0;
        virtual void setType(ComponentType type) = 0;
    };
} // namespace ECS
