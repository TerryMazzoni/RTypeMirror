/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Enum
*/

#pragma once
namespace ECS {
#define EntityId std::pair<EntityType, int>

#define Input std::tuple<EventType, int, std::optional<int>>

} // namespace ECS

enum class EntityType {
    Player,
    Enemy,
    Bullet,
    Background,
    Unknown
};

enum class EventType {
    Mouse,
    Keyboard,
};

enum class EventInput {
    Key_up,
    Key_down,
    Key_left,
    Key_right,
    Left_click,
    Right_click
};

enum class SceneType {
    Menu,
    Game,
    Pause,
    End,
    Unknown
};

enum class ComponentType {
    Color,
    Position,
    Rotation,
    Scale,
    Texture,
    Text,
    Unknown
};
