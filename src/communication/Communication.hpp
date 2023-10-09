/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Communication
*/

#pragma once

#include <string>

enum class ShipType {
    UNKNOW,
    PLAYER,
    ENEMY
};

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
        SHIPS,
        MISSILES,
        COLISION_ENTITIES,
    };

    typedef struct Header {
            CommunicationTypes type;
    } Header;

    typedef struct Position {
            float x;
            float y;
    } Position;

    typedef struct SpaceShip {
            Position position;
            int id;
            float life;
            int level;
            ShipType type;
    } SpaceShip;

    typedef struct Ships {
            CommunicationTypes code = CommunicationTypes::SHIPS;
            SpaceShip ship[32];
            size_t nbrItems;
    } ShipsPosition;

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
            float speed;
            int damage;
            int team_id;
            int id;
    } Missile;

    typedef struct MissilesPosition {
            CommunicationTypes code = CommunicationTypes::MISSILES;
            Missile missile[32];
            size_t nbrItems;
    } MissilesPosition;

    typedef struct CollisionEntities {
            CommunicationTypes code = CommunicationTypes::COLISION_ENTITIES;
            int id1;
            int id2;
    } CollisionEntities;
} // namespace Communication
