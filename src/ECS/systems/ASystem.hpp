/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** ASystem
*/

#ifndef ASYSTEM_HPP_
#define ASYSTEM_HPP_

#include "ISystem.hpp"

namespace ECS {
    class ASystem : public ISystem {
        public:
            virtual int execute() = 0;
            int setActivation(bool state);

        protected:
        private:
    };
} // namespace ECS

#endif /* !ASYSTEM_HPP_ */
