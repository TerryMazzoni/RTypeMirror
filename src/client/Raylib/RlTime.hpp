/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlTime
*/

#pragma once

#include "raylib.h"

namespace Raylib
{
    int getElapsedTime() {
        static double last = 0;
        double deltaTime = GetTime() - last;

        last = GetTime();
        return deltaTime;
    }
}
