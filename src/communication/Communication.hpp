/**
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
    ENEMY1,
    ENEMY2,
    BOSS1
};

enum class BonusType {
    UNKNOW,
    HEAL30,
    HEAL50,
    HEAL100,
    GUN1,
    GUN2,
    GUN3,
    SHIELD,
    MAX_HEALTH
};

/**
 * @brief Namespace containing all communications structures
*/
namespace Communication {

    enum class EventInput {
        Key_up = 265,
        Key_down = 264,
        Key_left = 263,
        Key_right = 262,
        Left_click = 0
    };

    enum class CommunicationTypes {
        UNKNOWN,
        ID,
        QUIT,
        TIMER,
        READY,
        SHIPS,
        MISSILES,
        COLISION,
        INPUT,
        BONUS,
        DELETE
    };

    /**
     * @brief Structure where we cast the received message to know the type of it
    */
    typedef struct Header {
            CommunicationTypes type;
    } Header;

    /**
     * @brief Structure to stock position
    */
    typedef struct Position {
            float x;
            float y;
    } Position;

    /**
     * @brief Structure to stock one spaceship
    */
    typedef struct SpaceShip {
            Position position;
            int id;
            float life;
            int level;
            float scale;
            ShipType type;
    } SpaceShip;

    /**
     * @brief Structure to communicate a list of spaceships
    */
    typedef struct ShipsList {
            CommunicationTypes code = CommunicationTypes::SHIPS;
            SpaceShip ship[32];
            size_t nbrItems;
    } ShipsPosition;

    /**
     * @brief Structure to communicate an id
    */
    typedef struct Id {
            CommunicationTypes code = CommunicationTypes::ID;
            int id;
    } Id;

    /**
     * @brief Structure to communicate a quit signal
    */
    typedef struct Quit {
            CommunicationTypes code = CommunicationTypes::QUIT;
    } Quit;

    /**
     * @brief Structure to communicate a timer
    */
    typedef struct Timer {
            CommunicationTypes code = CommunicationTypes::TIMER;
            int time = 0;
    } Timer;

    /**
     * @brief Structure to communicate the ready signal
    */
    typedef struct Ready {
            CommunicationTypes type = CommunicationTypes::READY;
            bool is_ready = false;
    } Ready;

    /**
     * @brief Structure to stock one missile
    */
    typedef struct Missile {
            Position position;
            Position direction;
            float speed;
            int damage;
            int team_id;
            int id;
    } Missile;

    /**
     * @brief Structure to communicate a list of missiles
    */
    typedef struct MissilesPosition {
            CommunicationTypes code = CommunicationTypes::MISSILES;
            Missile missile[32];
            size_t nbrItems;
    } MissilesPosition;

    /**
     * @brief Structure to communicate a colision
    */
    typedef struct Colision {
            CommunicationTypes code = CommunicationTypes::COLISION;
            int id1;
            int id2;
    } CollisionEntities;

    /**
     * @brief Structure to communicate a list of inputs
    */
    typedef struct Inputs {
            CommunicationTypes type = CommunicationTypes::INPUT;
            EventInput event[16];
            size_t nbrItems;
    } Inputs;

    /**
     * @brief Structure to stock a bonus
    */
    typedef struct Bonus {
            Position position;
            int id;
            BonusType type;
    } Bonus;

    /**
     * @brief Structure to communicate a list of bonus
    */
    typedef struct BonusPosition {
            CommunicationTypes code = CommunicationTypes::BONUS;
            Bonus bonus[32];
            size_t nbrItems;
    } BonusPosition;

    /**
     * @brief Structure to communicate the delete signal
    */
    typedef struct Delete {
            CommunicationTypes code = CommunicationTypes::DELETE;
            int id;
    } Delete;
}; // namespace Communication
