/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Text
*/

#pragma once

#include <string>

#include "AComponent.hpp"
#include "RlText.hpp"

namespace ECS
{
    class Text : public AComponent
    {
    public:
        Text();
        Text(const std::string text);
        ~Text();

        int setValue(std::string value);
        std::any getValue() const;

    protected:
    private:
        std::string _text;
    };
} // namespace ECS
