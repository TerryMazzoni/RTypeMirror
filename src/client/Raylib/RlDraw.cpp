/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlDraw
*/

#include "RlDraw.hpp"

namespace Raylib
{
    void clear(Color color)
    {
        ClearBackground(color);
    }

    void beginDraw()
    {
        BeginDrawing();
    }

    void endDraw()
    {
        EndDrawing();
    }

    void draw(Texture2D texture, int x, int y, Color color)
    {
        DrawTexture(texture, x, y, color);
    }

    void drawEx(Texture2D texture, Vector2 position, Vector2 values, Color color)
    {
        DrawTextureEx(texture, position, values.x, values.y, color);
    }
}
