/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlDraw
*/

#include "RlDraw.hpp"

namespace Raylib
{
    void clear(RlColor color)
    {
        ClearBackground(color.getColor());
    }

    void beginDraw()
    {
        BeginDrawing();
    }

    void endDraw()
    {
        EndDrawing();
    }
}
