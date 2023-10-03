/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** ASystem
*/

#include "ASystem.hpp"

namespace ECS {
    int ASystem::setActivation(bool state)
    {
        _isActivated = state;
    }
} // namespace ECS
