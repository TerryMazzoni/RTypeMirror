/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlText
*/

#pragma once

#include <string>

#include "raylib.h"
#include "RlColor.hpp"
#include "RlFont.hpp"

namespace Raylib
{
    void drawText(std::string text, Vector3 values, RlColor color = RlColor(255, 255, 255));
    void drawTextEx(RlFont font, std::string text, Vector4 values, RlColor color = RlColor(255, 255, 255));
}
