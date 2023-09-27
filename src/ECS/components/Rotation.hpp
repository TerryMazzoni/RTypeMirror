/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Rotation
*/

#pragma once

#include "AComponent.hpp"

namespace ECS
{
    class Rotation : public AComponent<float>
    {
    public:
        Rotation();
        Rotation(float value);
        ~Rotation();

        int setValue(float value);
        float getValue() const;

    protected:
    private:
        float _degree;
    };
} // namespace ECS
