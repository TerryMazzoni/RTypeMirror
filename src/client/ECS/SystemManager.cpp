/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** SystemManager
*/

#include "SystemManager.hpp"


namespace ECS {

    std::vector<Action> SystemManager::execute()
    {
        std::vector<Action> result;
    
        _listActions.clear();
        for (auto &system : _listSystems) {
            result = system->execute();
            for (auto &action : result) {
                _listActions.push_back(action);
            }
        }
        return _listActions;
    }

    void SystemManager::addSystems(std::vector<std::shared_ptr<ISystem>> listSystems)
    {
        for (auto &system : listSystems) {
            _listSystems.push_back(system);
        }
    }

} // namespace ECS
