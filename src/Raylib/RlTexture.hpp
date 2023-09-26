/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlTexture
*/

#pragma once

#include <string>

#include "raylib.h"
#include "RlColor.hpp"

namespace Raylib
{
    class RlTexture
    {
    public:
        RlTexture();
        RlTexture(std::string path);
        ~RlTexture();

        /**
         * @brief Draw the texture
         *
         * @param x x position of the texture
         * @param y y position of the texture
         * @param color Color of the texture (default: white)
         */
        void draw(int x, int y, RlColor color = RlColor(255, 255, 255));
        /**
         * @brief Draw the texture with extended parameters
         *
         * @param position Vector2 containing the x and y position of the texture
         * @param rotation Rotation of the texture
         * @param scale Scaling of the texture
         * @param color Color of the texture (default: white)
         */
        void drawEx(Vector2 position, float rotation, float scale, RlColor color = RlColor(255, 255, 255));
        /**
         * @brief Unload the texture
         *
         */
        void unload();
        /**
         * @brief Get the Width of the texture
         *
         * @return int
         */
        int getWidth() const;
        /**
         * @brief Get the Height of the texture
         *
         * @return int
         */
        int getHeight() const;
        /**
         * @brief Set the Texture object
         *
         * @param path Path to the texture
         */
        void setTexture(std::string path);

    private:
        Texture2D _texture;
    };
}
