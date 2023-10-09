/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** BulletMouvement
*/

#pragma once

#include "ASystem.hpp"

namespace ECS
{
    class BulletMouvement : public ASystem
    {
    public:
        BulletMouvement();
        ~BulletMouvement() = default;

        /**
         * @brief Execute the mouvement for a bullet 
         * 
         * @return std::vector<Action> 
         */
        std::vector<Action> execute();
    };
}
