/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlInputs
*/

#include "RlInputs.hpp"
#include <iostream>

static const std::vector<EventInput> inputTypes = {
    EventInput::Key_up,
    EventInput::Key_down,
    EventInput::Key_left,
    EventInput::Key_right
};

namespace Raylib
{
    std::set<Input> getInputs()
    {
        static std::set<Input> inputs;
        int tmp = 0;
        std::pair<int, int> mousePos = getMousePos();

        for (auto event : inputTypes) {
            if (IsKeyReleased((int)event))
                inputs.erase({EventType::Keyboard, (int)event, std::nullopt});
        }
        while ((tmp = GetKeyPressed()))
            inputs.insert(std::tuple(EventType::Keyboard, tmp, std::nullopt));
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            inputs.insert(std::tuple(EventType::Mouse, mousePos.first, mousePos.second));
        return inputs;
    }

    std::pair<int, int> getMousePos()
    {
        return std::pair(GetMouseX(), GetMouseY());
    }
}
