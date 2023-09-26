/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlInputs
*/

#include "RlInputs.hpp"

namespace Raylib
{
    std::vector<Input> getInputs()
    {
        std::vector<Input> inputs;
        int tmp = 0;
        std::pair<int, int> mousePos = getMousePos();

        while ((tmp = GetKeyPressed()))
            inputs.push_back(std::tuple(EventType::Keyboard, tmp, std::nullopt));
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            inputs.push_back(std::tuple(EventType::Mouse, mousePos.first, mousePos.second));
        return inputs;
    }

    std::pair<int, int> getMousePos()
    {
        return std::pair(GetMouseX(), GetMouseY());
    }
}
