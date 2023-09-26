/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Scale
*/

#pragma once

#include "AComponent.hpp"

namespace ECS
{
    class Scale : public AComponent<float>
    {
    public:
        Scale();
        ~Scale();

        int setValue(float value);
        float getValue() const;

    protected:
    private:
        float _scale;
    };
} // namespace ECS
