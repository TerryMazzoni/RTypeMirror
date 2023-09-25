/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Enum
*/

#ifndef ENUM_HPP_
#define ENUM_HPP_

namespace ECS {
#define Entity std::pair<EntityType, int>

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

enum EventInput {
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

#endif /* !ENUM_HPP_ */
