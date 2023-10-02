/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Text
*/

#pragma once

#include <string>

namespace ECS
{
    struct Text
    {
        Text() : text("default") {};
        Text(std::string text) : text(text) {};

        std::string text;
    };
    
} // namespace ECS
