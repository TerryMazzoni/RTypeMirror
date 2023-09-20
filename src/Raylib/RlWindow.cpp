/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlWindow
*/

#include "RlWindow.hpp"

namespace Raylib {
    void cursor()
    {
        if (IsCursorHidden())
            ShowCursor();
        else
            HideCursor();
    }

    void fullscreen()
    {
        ToggleFullscreen();
    }

    bool windowShouldClose()
    {
        return WindowShouldClose();
    }

    void initWindow(int width, int height, const std::string title, int fps)
    {
        SetTraceLogLevel(LOG_WARNING);
        InitWindow(width, height, title.c_str());
        SetTargetFPS(fps);
    }

    void closeWindow()
    {
        CloseWindow();
    }
}