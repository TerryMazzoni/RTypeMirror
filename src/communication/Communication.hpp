/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** ICommunication
*/

#pragma once

#include <string>

namespace Communication {

    enum class EventInput {
        Key_up,
        Key_down,
        Key_left,
        Key_right,
        Left_click
    };

    enum class CommunicationTypes {
        UNKNOWN,
        ID,
        QUIT,
        TIMER,
        READY,
        MATES_POSITION,
        ENNEMIES_POSITION,
        MISSILES_POSITION,
        COLISION_ENTITIES,
        INPUT
    };

    typedef struct Header {
            CommunicationTypes type;
    } Header;

    typedef struct Position {
            float x;
            float y;
    } Position;

    typedef struct MatesPosition {
            CommunicationTypes code = CommunicationTypes::MATES_POSITION;
            Position position[4];
            size_t nbrItems;
    } MatesPosition;

    typedef struct Ennemy {
            Position position;
            int id;
    } Ennemy;

    typedef struct EnnemiesPosition {
            CommunicationTypes code = CommunicationTypes::ENNEMIES_POSITION;
            Ennemy ennemy[64];
            size_t nbrItems;
    } EnnemiesPosition;

    typedef struct Id {
            CommunicationTypes code = CommunicationTypes::ID;
            int id;
    } Id;

    typedef struct Quit {
            CommunicationTypes code = CommunicationTypes::QUIT;
    } Quit;

    typedef struct Timer {
            CommunicationTypes code = CommunicationTypes::TIMER;
            int time = 0;
    } Timer;

    typedef struct Ready {
            CommunicationTypes type = CommunicationTypes::READY;
            bool is_ready = false;
    } Ready;

    typedef struct Missile {
            Position position;
            Position direction;
            Position rect;
            float speed;
            int damage;
            int team_id;
            int id;
    } Missile;

    typedef struct MissilesPosition {
            CommunicationTypes code = CommunicationTypes::MISSILES_POSITION;
            Missile missile[32];
            size_t nbrItems;
    } MissilesPosition;

    typedef struct CollisionEntities {
            CommunicationTypes code = CommunicationTypes::COLISION_ENTITIES;
            int id1;
            int id2;
    } CollisionEntities;

    typedef struct Input {
            CommunicationTypes type = CommunicationTypes::INPUT;
            EventInput event[16];
            size_t nbrItems;
    } Input;

} // namespace Communication