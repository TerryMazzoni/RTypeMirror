/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** ICommunication
*/

#pragma once

#include <string>

namespace Communication {
    enum class CommunicationTypes {
        UNKNOWN,
        ID,
        QUIT,
        TIMER,
        READY,
        POSITION,
        NEW_MATES_POSITION,
        NEW_MISSILES_POSITION,
        NEW_HIT_BETWEEN_ELEMENTS,
    };

    typedef struct Header {
            CommunicationTypes type;
    } Header;

    typedef struct Id {
            CommunicationTypes type = CommunicationTypes::ID;
            int id = 0;
    } Id;

    typedef struct Quit {
            CommunicationTypes type = CommunicationTypes::QUIT;
    } Quit;

    typedef struct Timer {
            CommunicationTypes type = CommunicationTypes::TIMER;
            int time = 0;
    } Timer;

    typedef struct Ready {
            CommunicationTypes type = CommunicationTypes::READY;
            bool is_ready = false;
    } Ready;

} // namespace Communication