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
            std::string getSceneId() const;
            int executeInputs(std::vector<std::tuple<EventType, int, std::optional<int>>>);

        protected:
        private:
            std::string _idScene;
            std::vector<std::tuple<EventType, int, std::optional<int>>> _listEvent;
    };
} // namespace ECS

#endif /* !EVENTMANAGER_HPP_ */
