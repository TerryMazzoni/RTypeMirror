/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlInputs
*/

#pragma once

#include <vector>
#include <optional>
#include <tuple>

#include "raylib.h"

namespace Raylib {
    std::vector<std::tuple<int, int, std::optional<int>>> getInputs();
    std::pair<int, int> getMousePos();
}
