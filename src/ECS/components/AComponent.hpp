/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** AComponent
*/

#ifndef ACOMPONENT_HPP_
#define ACOMPONENT_HPP_

#include "IComponent.hpp"

namespace ECS {
    template <typename T>
    class AComponent : public IComponent {
        public:
            virtual int setValue(T value) = 0;
            virtual T getValue() const = 0;
            int AddId(std::pair<EntityType, int>);
            int RemoveId(std::pair<EntityType, int>);

        protected:
        private:
    };
} // namespace ECS

#endif /* !ACOMPONENT_HPP_ */
