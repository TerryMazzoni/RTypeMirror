/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** SystemManager
*/

#include "SystemManager.hpp"

namespace ECS {
    SystemManager::SystemManager()
    {
    }

    SystemManager::~SystemManager()
    {
    }

    int SystemManager::execute(SceneType scene)
    {
        for (auto &system : _listSystems[scene]) {
            system->execute();
        }
        return 0;
    }
}
