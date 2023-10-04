/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlText
*/

#include "RlText.hpp"

namespace Raylib
{
    void drawText(std::string text, Vector3 values, RlColor color)
    {
        DrawText(text.c_str(), values.x, values.y, values.z, color.getColor());
    }

    void drawTextEx(RlFont font, std::string text, Vector4 values, RlColor color)
    {
        DrawTextEx(font.getFont(), text.c_str(), Vector2({values.x, values.y}), values.z, values.w, color.getColor());
    }
}
