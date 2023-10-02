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

    void draw(RlTexture texture, int x, int y, RlColor color)
    {
        DrawTexture(texture.getTexture(), x, y, color.getColor());
    }

    void drawEx(RlTexture texture, Vector2 position, Vector2 values, RlColor color)
    {
        DrawTextureEx(texture.getTexture(), position, values.x, values.y, color.getColor());
    }
}
