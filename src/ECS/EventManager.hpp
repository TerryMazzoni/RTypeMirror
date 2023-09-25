/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** EventManager
*/

#ifndef EVENTMANAGER_HPP_
#define EVENTMANAGER_HPP_

#include <string>
#include <vector>
#include <tuple>
#include <optional>
#include "Enum.hpp"

namespace ECS {
    class EventManager {
        public:
            EventManager();
            ~EventManager();
            SceneType getSceneId() const;
            int executeInputs(std::vector<Input>);

        protected:
        private:
            SceneType _scene;
            std::vector<Input> _listEvent;
    };
} // namespace ECS

#endif /* !EVENTMANAGER_HPP_ */
