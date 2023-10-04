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

    std::vector<Action> SystemManager::execute()
    {
        _listActions.clear();
        for (auto &system : _listSystems) {
            system.execute();
        }
        return _listActions;
    }

    void SystemManager::addSystems(std::vector<ISystem> listSystems)
    {
        _listSystems.insert(_listSystems.end(), listSystems.begin(), listSystems.end());
    }

    void SystemManager::removeSystems(std::vector<ISystem> listSystems)
    {
        for (auto &system : listSystems) {
            _listSystems.erase(std::remove(_listSystems.begin(), _listSystems.end(), system), _listSystems.end());
        }
    }
} // namespace ECS
