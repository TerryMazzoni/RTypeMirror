/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** ICommunication
*/

#pragma once

#include <string>

enum class Communication {
    ID,
    QUIT,
    TIMER,
    POSITION,
    NEW_MATES_POSITION,
    NEW_MISSILES_POSITION,
    NEW_HIT_BETWEEN_ELEMENTS,
    UNKNOWN
};