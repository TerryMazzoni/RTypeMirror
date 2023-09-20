/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Enum
*/

#ifndef ENUM_HPP_
#define ENUM_HPP_

enum EntityType {
    PLAYER,
    ENEMY,
    BULLET,
    BACKGROUND,
    UNKNOWN
};

enum EventType {
    MOUSE,
    KEYBOARD,
};

enum EventInput {
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    LEFT_CLICK,
    RIGHT_CLICK
};

#endif /* !ENUM_HPP_ */
