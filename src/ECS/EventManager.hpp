/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** EventManager
*/

#pragma once

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
