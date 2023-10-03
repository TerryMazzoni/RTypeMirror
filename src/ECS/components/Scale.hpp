/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Scale
*/

#pragma once

namespace ECS {
    struct Scale {
            Scale()
                : scale(1){};
            Scale(float scale)
                : scale(scale){};

            float scale;
    };

} // namespace ECS
