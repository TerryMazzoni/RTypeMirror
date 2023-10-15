/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Shoot
*/

#pragma once

#include "ASystem.hpp"

namespace ECS {
    class Shoot : public ASystem {
        public:
            Shoot();
            ~Shoot() = default;

            /**
             * @brief Execute the Shoot system for the spaceship
             *
             * @return std::vector<Action>
             */
            std::vector<Action> execute();

        private:
            int _count;
    };
} // namespace ECS
