/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Texture
*/

#pragma once

#include "RlTexture.hpp"

namespace ECS
{
    struct Texture
    {
        Texture() : texture() {};
        Texture(std::string path) : texture(path) {};
        Texture(Raylib::RlTexture texture) : texture(texture) {};

        Raylib::RlTexture texture;
    };
    
} // namespace ECS
