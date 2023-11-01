/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** BackgroundMouvement
*/

#pragma once

#include "ASystem.hpp"

namespace ECS {
    class BackgroundMouvement : public ASystem {
        public:
            BackgroundMouvement(int start, int end);
            ~BackgroundMouvement() = default;

            /**
             * @brief Execute the mouvement for a Background
             *
             * @return std::vector<Action>
             */
            std::vector<Action> execute();
        private:
            int _start;
            int _end;
    };
} // namespace ECS
