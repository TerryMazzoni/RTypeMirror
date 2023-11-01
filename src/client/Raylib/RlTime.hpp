/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlTime
*/

#pragma once

extern "C" {
    #include "raylib.h"
}

namespace Raylib
{
    double getElapsedTime() {
        static double last = 0;
        double deltaTime = GetTime() - last;

        last = GetTime();
        return deltaTime;
    }
}
