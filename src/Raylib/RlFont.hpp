/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlFont
*/

#pragma once

#include <string>

#include "raylib.h"

namespace Raylib
{
    class RlFont
    {
    public:
        RlFont(std::string path);
        ~RlFont();

        void unload();
        Font getFont() const;

    private:
        Font _font;
    };
}
