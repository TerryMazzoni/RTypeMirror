/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** ISystem
*/

#pragma once

#include "Enum.hpp"
namespace ECS {
    class ISystem {
        public:
            virtual ~ISystem() = default;

            virtual std::vector<Action> execute() = 0;
            virtual int setActivation(bool state) = 0;
    };
} // namespace ECS
