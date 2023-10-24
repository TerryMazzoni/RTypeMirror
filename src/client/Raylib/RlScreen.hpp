/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlScreen
*/

#pragma once

extern "C" {
    #include "raylib.h"
}

namespace Raylib
{
    /**
     * @brief Get the Screen Width
     *
     * @return int
     */
    int getScreenWidth();
    /**
     * @brief Get the Screen Height
     *
     * @return int
     */
    int getScreenHeight();
}
