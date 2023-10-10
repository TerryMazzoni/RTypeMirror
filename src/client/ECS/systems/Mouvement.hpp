/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Mouvement
*/

#pragma once

#include "ASystem.hpp"

namespace ECS
{

    class Mouvement : public ASystem
    {
    public:
        Mouvement();
        ~Mouvement() = default;

        /**
         * @brief Execute the system logic
         *
         * @return std::vector<Action>
         */
        std::vector<Action> execute();

    private:
        bool _goRight;
    };

}
