/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Rotation
*/

#pragma once

#include <string>

#include "AComponent.hpp"

namespace ECS
{
    class Rotation : public AComponent
    {
    public:
        Rotation();
        Rotation(float value);
        ~Rotation();

        int setValue(std::string value);
        std::any getValue() const;

    protected:
    private:
        float _degree;
    };
} // namespace ECS
