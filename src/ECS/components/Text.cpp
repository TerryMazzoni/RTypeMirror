/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Text
*/

#include "Text.hpp"

namespace ECS
{
    Text::Text()
    {
    }

    Text::~Text()
    {
    }

    int Text::setValue(std::string value)
    {
        _text = value;
        return 0;
    }

    std::string Text::getValue() const
    {
        return _text;
    }
} // namespace ECS
