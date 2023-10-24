/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlFont
*/

#pragma once

#include <string>

extern "C" {
    #include "raylib.h"
}

namespace Raylib
{
    class RlFont
    {
    public:
        RlFont(std::string path);
        ~RlFont();

        /**
         * @brief Unload the font
         *
         */
        void unload();
        /**
         * @brief Get the Font object
         *
         * @return Font
         */
        Font getFont() const;

    private:
        Font _font;
    };
}
