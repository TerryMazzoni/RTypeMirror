/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlFont
*/

#include "RlFont.hpp"

namespace Raylib
{
    void RlFont::unload()
    {
        UnloadFont(_font);
    }

    Font RlFont::getFont() const
    {
        return (_font);
    }

    RlFont::RlFont(std::string path)
    {
        _font = LoadFont(path.c_str());
    }

    RlFont::~RlFont()
    {
    }
}