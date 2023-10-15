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

    void SystemManager::removeSystems(std::vector<Entity> entitiesToRemove)
    {
        for (auto &entity : entitiesToRemove) {
            for (int i = 0; i < _listSystems.size(); i++) {
                if (!_listSystems[i]->getEntity().has_value())
                    continue;
                if (_listSystems[i]->getEntity().value().id.first == entity.id.first && _listSystems[i]->getEntity().value().id.second == entity.id.second) {
                    _listSystems.erase(_listSystems.begin() + i);
                }
            }
        }
    }

} // namespace ECS
