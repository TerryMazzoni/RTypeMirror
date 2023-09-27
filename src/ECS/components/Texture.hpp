/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Texture
*/

#pragma once

#include "AComponent.hpp"
#include "RlTexture.hpp"

namespace ECS
{
    class Texture : public AComponent<Raylib::RlTexture>
    {
    public:
        Texture();
        Texture(const std::string texture);
        Texture(Raylib::RlTexture value);
        ~Texture();

        int setValue(const std::string texture);
        int setValue(Raylib::RlTexture value);
        Raylib::RlTexture getValue() const;

    protected:
    private:
        Raylib::RlTexture _texture;
    };
} // namespace ECS
