/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** IComponent
*/

#pragma once

#include <vector>
#include "Enum.hpp"

namespace ECS
{
    class IComponentBase
    {
    public:
        virtual ~IComponentBase() = default;
    };
    template <typename T>
    class IComponent : public IComponentBase
    {
    public:
        virtual ~IComponent() = default;

        virtual int setValue(T value) = 0;
        virtual T getValue() const = 0;
        virtual int AddId(EntityId) = 0;
        virtual int RemoveId(EntityId) = 0;
    };
} // namespace ECS
