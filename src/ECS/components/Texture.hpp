/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Texture
*/

#pragma once

#include <string>

#include "AComponent.hpp"
#include "RlTexture.hpp"

namespace ECS
{
    class Texture : public AComponent
    {
    public:
        Texture();
        Texture(const std::string texture);
        Texture(Raylib::RlTexture value);
        ~Texture();

        int setValue(const std::string texture);
        std::any getValue() const;

    protected:
    private:
        Raylib::RlTexture _texture;
    };
} // namespace ECS
