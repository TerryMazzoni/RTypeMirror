/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** AComponent
*/

#pragma once

#include "IComponent.hpp"

namespace ECS
{
    template <typename T>
    class AComponent : public IComponent<T>
    {
    public:
        virtual int setValue(T value) = 0;
        virtual T getValue() const = 0;
        int AddId(EntityId);
        int RemoveId(EntityId);

    protected:
        std::vector<EntityId> _listEntities;
    };
} // namespace ECS
