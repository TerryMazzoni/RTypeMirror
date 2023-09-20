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
    /**
     * @brief Init the window
     *
     * @param width Width of the window
     * @param height Height of the window
     * @param title Title of the window
     * @param fps Framerate of the window
     */
    void initWindow(int width, int height, const std::string title, int fps);
    /**
     * @brief Close the window
     *
     */
    void closeWindow();
    /**
     * @brief Check if the window should close
     *
     * @return bool
     */
    bool windowShouldClose();
    /**
     * @brief Toggle fullscreen
     *
     */
    void fullscreen();
    /**
     * @brief Toggle cursor
     *
     */
    void cursor();
};
