/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Rotation
*/

#pragma once

namespace ECS {
    struct Rotation {
            Rotation()
                : angle(0){};
            Rotation(float angle)
                : angle(angle){};

            float angle;
    };

} // namespace ECS
