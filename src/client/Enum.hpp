/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Enum
*/

#pragma once

#define EntityId std::pair<EntityType, int>

#define Input std::tuple<EventType, int, std::optional<int>>

enum class EntityType {
    Player,
    Enemy1,
    Enemy2,
    Boss1,
    Bullet,
    Background1,
    Background2,
    Background3,
    Unknown
};

enum class EventType {
    Mouse,
    Keyboard,
};

enum class EventInput {
    Key_up = 265,
    Key_down = 264,
    Key_left = 263,
    Key_right = 262,
    Space = 32,
};

enum class ActionType {
    Move,
    Shoot,
    ChangeTexture,
    UpdatePosPlayer,
    UpdatePosEnemy,
    Unknown
};

enum class SceneType {
    Menu,
    Game,
    Pause,
    End,
    Unknown
};

enum class ComponentType {
    Sprite,
    Music,
    Sound,
    Weapon,
    Unknown
};
