/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** IComponent
*/

#ifndef ICOMPONENT_HPP_
#define ICOMPONENT_HPP_

#include <vector>
#include "Enum.hpp"

namespace ECS {
    template <typename T>
    class IComponent {
        public:
            virtual ~IComponent() = default;

            virtual int setValue(T value) = 0;
            virtual T getValue() const = 0;
            virtual int AddId(std::pair<EntityType, int>) = 0;
            virtual int RemoveId(std::pair<EntityType, int>) = 0;

        protected:
            std::vector<std::pair<EntityType, int>> _ids;
    };
} // namespace ECS

#endif /* !ICOMPONENT_HPP_ */
