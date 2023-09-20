/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlWindow
*/

#pragma once

#include <string>
#include <raylib.h>

namespace Raylib
{
    void initWindow(int width, int height, const std::string title, int fps);
    void closeWindow();
    bool windowShouldClose();
    void fullscreen();
    void cursor();
};