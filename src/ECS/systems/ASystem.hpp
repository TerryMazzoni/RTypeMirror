/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** ASystem
*/

#pragma once

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
