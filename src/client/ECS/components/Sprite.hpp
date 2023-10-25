/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Sprite
*/

#pragma once

#include <vector>
#include <any>
#include <string>
#include "Component.hpp"

namespace ECS {
    class Sprite : public Component {
        public:
            ~Sprite() = default;
            /**
             * @brief Set the Position object
             * 
             * @param x 
             * @param y 
             */
            virtual void setPosition(const int x, const int y) = 0;
            /**
             * @brief Set the Position object
             * 
             * @param positions 
             */
            virtual void setPosition(std::pair<int, int> positions) = 0;
            /**
             * @brief Set the Textures object
             * 
             * @param pathTextures 
             * @param textureIndexes 
             */
            virtual void setTextures(const std::vector<std::string> pathTextures, std::vector<int> textureIndexes) = 0;
            /**
             * @brief Set the Color object
             * 
             * @param r 
             * @param g 
             * @param b 
             * @param a 
             * @param textureToApply 
             */
            virtual void setColor(const int r, const int g, const int b, const int a, std::vector<int> textureToApply) = 0;
            /**
             * @brief Set the Scale object
             * 
             * @param scale 
             */
            virtual void setScale(const float scale) = 0;
            /**
             * @brief Set the Rotation object
             * 
             * @param rotation 
             */
            virtual void setRotation(const float rotation) = 0;

            /**
             * @brief Get the Pos object
             * 
             * @return std::pair<int, int> 
             */
            virtual std::pair<int, int> getPos() const = 0;
            /**
             * @brief Get the Pos X object
             * 
             * @return int 
             */
            virtual int getPosX() const = 0;
            /**
             * @brief Get the Pos Y object
             * 
             * @return int 
             */
            virtual int getPosY() const = 0;
            /**
             * @brief Get the Textures To Display object
             * 
             * @return std::vector<std::any> 
             */
            virtual std::vector<std::any> getTexturesToDisplay() const = 0;
            /**
             * @brief Get the red color of the sprite
             * 
             * @return int 
             */
            virtual int getR() const = 0;
            /**
             * @brief Get the green color of the sprite
             * 
             * @return int 
             */
            virtual int getG() const = 0;
            /**
             * @brief Get the blue color of the sprite
             * 
             * @return int 
             */
            virtual int getB() const = 0;
            /**
             * @brief Get the alpha value of the sprite
             * 
             * @return int 
             */
            virtual int getA() const = 0;
            /**
             * @brief Get the Scale object
             * 
             * @return float 
             */
            virtual float getScale() const = 0;
            /**
             * @brief Get the Rotation object
             * 
             * @return float 
             */
            virtual float getRotation() const = 0;

            /**
             * @brief Move the sprite
             * 
             * @param velocity 
             */
            virtual void move(const std::pair<int, int> velocity) = 0;
            /**
             * @brief Animate the texture of the sprite
             * 
             */
            virtual void animateTextures() = 0;
    };
} // namespace ECS
