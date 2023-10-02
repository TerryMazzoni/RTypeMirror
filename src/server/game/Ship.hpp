/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Ship
*/

#pragma once

#include "Position.hpp"

enum class ShipType
{
    UNKNOW,
    PLAYER,
    ENEMY
};

class Ship
{
public:
    /**
     * @brief Construct a new Ship object
     */
    Ship();
    /**
     * @brief Construct a new Ship object
     *
     * @param pos
     * @param id
     * @param type
     */
    Ship(Coords pos, int id, ShipType type);
    /**
     * @brief Destroy the Ship object
     */
    ~Ship();
    /**
     * @brief Set the Pos object
     *
     * @param pos
     */
    void setPos(Coords pos);
    /**
     * @brief Set the Speed object
     *
     * @param speed
     */
    void setSpeed(float speed);
    /**
     * @brief Set the Life object
     *
     * @param life
     */
    void setLife(float life);
    /**
     * @brief Set the Id object
     *
     * @param id
     */
    void setId(int id);
    /**
     * @brief Set the Level object
     *
     * @param level
     */
    void setLevel(int level);
    /**
     * @brief Set the Type object
     *
     * @param type
     */
    void setType(ShipType type);
    /**
     * @brief Get the Pos object
     *
     * @return Coords
     */
    Coords getPos() const;
    /**
     * @brief Get the Speed object
     *
     * @return float
     */
    float getSpeed() const;
    /**
     * @brief Get the Life object
     *
     * @return float
     */
    float getLife() const;
    /**
     * @brief Get the Id object
     *
     * @return int
     */
    int getId() const;
    /**
     * @brief Get the Level object
     *
     * @return int
     */
    int getLevel() const;
    /**
     * @brief Get the Type object
     *
     * @return ShipType
     */
    ShipType getType() const;

private:
    Coords _pos;
    float _speed;
    float _life;
    int _id;
    int _level;
    ShipType _type;
};
