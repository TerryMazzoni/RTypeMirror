/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Scale
*/

#pragma once

#include <string>

#include "AComponent.hpp"

namespace ECS
{
    class Scale : public AComponent
    {
    public:
        Scale();
        Scale(float value);
        ~Scale();

        int setValue(std::string value);
        std::any getValue() const;

    protected:
    private:
        float _scale;
    };
} // namespace ECS
