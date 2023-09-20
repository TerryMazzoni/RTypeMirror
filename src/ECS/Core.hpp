/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include "Enum.hpp"
#include "EntitiesManager.hpp"
#include "EventManager.hpp"
#include "Graph.hpp"
#include "SystemManager.hpp"

namespace ECS {
    template <typename T>
    class Core {
        public:
            Core();
            ~Core();

        protected:
        private:
            EntitiesManager<T> _entitiesManager;
            EventManager _eventManager;
            Graph _graph;
            SystemManager _systemManager;
    };
} // namespace ECS

#endif /* !CORE_HPP_ */
