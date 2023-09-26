/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** AComponent
*/

#include "AComponent.hpp"

namespace ECS {
    template <typename T>
    int AComponent<T>::AddId(Entity id) {
        _listEntities.push_back(id);
        return 0;
    }

    template <typename T>
    int AComponent<T>::RemoveId(Entity id) {
        for (int i = 0; i < _listEntities.size(); i++) {
            if (_listEntities[i].first == id.first && _listEntities[i].second == id.second) {
                _listEntities.erase(_listEntities.begin() + i);
                return 0;
            }
        }
        return 1;
    }
} // namespace ECS
