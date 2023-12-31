/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlInputs
*/

#pragma once

#include <set>
#include <vector>
#include <optional>
#include <tuple>

#include "Enum.hpp"
extern "C" {
    #include "raylib.h"
}

namespace Raylib
{
    /**
     * @brief Get the Inputs of the user
     *
     * @return std::vector<std::tuple<int, int, std::optional<int>>>
     */
    std::set<Input> getInputs();
}
