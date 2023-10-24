/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlTexture
*/

#pragma once

#include <string>

extern "C" {
    #include "raylib.h"
}

namespace Raylib
{
    class RlTexture
    {
    public:
        RlTexture();
        RlTexture(std::string path);
        ~RlTexture();

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
         * @param std::string Path to the texture
         */
        void setTexture(std::string path);
        /**
         * @brief Get the Texture object
         *
         * @return Texture2D
         */
        Texture2D getTexture() const;

    private:
        Texture2D _texture;
    };
}
