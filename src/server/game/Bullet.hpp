/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Bullet
*/

#pragma once

#include "Position.hpp"

class Bullet
{
public:
    /**
     * @brief Construct a new Bullet object
     */
    Bullet();
    /**
     * @brief Construct a new Bullet object
     *
     * @param pos
     * @param direction
     * @param speed
     * @param damage
     * @param id
     */
    Bullet(Coords pos, Coords direction, float speed, float damage, int id);
    /**
     * @brief Destroy the Bullet object
     */
    ~Bullet();
    /**
     * @brief Set the Pos object
     *
     * @param pos
     */
    void setPos(Coords pos);
    /**
     * @brief Set the Direction object
     *
     * @param direction
     */
    void setDirection(Coords direction);
    /**
     * @brief Set the Speed object
     *
     * @param speed
     */
    void setSpeed(float speed);
    /**
     * @brief Set the Damage object
     *
     * @param damage
     */
    void setDamage(float damage);
    /**
     * @brief Set the Id object
     *
     * @param id
     */
    void setId(int id);
    /**
     * @brief Get the Pos object
     *
     * @return Coords
     */
    Coords getPos() const;
    /**
     * @brief Get the Direction object
     *
     * @return Coords
     */
    Coords getDirection() const;
    /**
     * @brief Get the Speed object
     *
     * @return float
     */
    float getSpeed() const;
    /**
     * @brief Get the Damage object
     *
     * @return float
     */
    float getDamage() const;
    /**
     * @brief Get the Id object
     *
     * @return int
     */
    int getId() const;

private:
    Coords _pos;
    Coords _direction;
    float _speed;
    float _damage;
    int _id;
};
