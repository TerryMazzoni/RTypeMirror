/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** AComponent
*/

#pragma once

#include <vector>

#include "IComponent.hpp"

namespace ECS
{
    template <typename T>
    class AComponent : public IComponent<T>
    {
    public:
        virtual int setValue(T value) = 0;
        virtual T getValue() const = 0;
        int AddId(EntityId id)
        {
            _listEntities.push_back(id);
            return 0;
        };
        int RemoveId(EntityId id)
        {
            for (std::size_t i = 0; i < _listEntities.size(); i++)
            {
                if (_listEntities[i].first == id.first && _listEntities[i].second == id.second)
                {
                    _listEntities.erase(_listEntities.begin() + i);
                    return 0;
                }
            }
            return 1;
        };
        ComponentType getType() const;
        void setType(ComponentType type);

    protected:
        std::vector<EntityId> _listEntities;
        ComponentType _type;
    }; // namespace ECS
}
