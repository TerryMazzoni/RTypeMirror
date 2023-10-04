/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** EventManager
*/

#pragma once

#include <string>
#include <vector>
#include <set>
#include <tuple>
#include <any>
#include <optional>
#include "Enum.hpp"
#include "Entity.hpp"

namespace ECS {
    class EventManager {
        public:
            EventManager();
            ~EventManager();
            void setMyPlayer(Entity my);
            int executeInputs(std::set<Input>);
            std::vector<Action> getActions() const;

        private:
            void movePlayer(EventInput dir);

            Entity _myPlayer;
            std::vector<Action> _actions;
    };
} // namespace ECS
