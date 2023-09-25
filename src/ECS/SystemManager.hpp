/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** SystemManager
*/

#ifndef SYSTEMMANAGER_HPP_
#define SYSTEMMANAGER_HPP_

#include <string>
#include <map>
#include <vector>

namespace ECS {
    class SystemManager {
        public:
            SystemManager();
            ~SystemManager();

            int execute(SceneType scene);

        protected:
        private:
            std::map<SceneType, std::vector<void *>> _listSystems; // replace void * with class system
    };
} // namespace ECS

#endif /* !SYSTEMMANAGER_HPP_ */
