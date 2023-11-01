/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlSprite
*/

#pragma once

#include <utility>
#include <any>
#include "Sprite.hpp"
extern "C" {
    #include "raylib.h"
}

namespace Raylib {
    class RlSprite : public ECS::Sprite {
        public:
            /**
             * @brief Construct a new Rl Sprite
             * 
             */
            RlSprite();
            /**
             * @brief Construct a new Rl Sprite with position
             * 
             * @param x 
             * @param y 
             */
            RlSprite(const int x, const int y);
            /**
             * @brief Construct a new Rl Sprite with texture
             * 
             * @param pathTextures vector of string
             * @param textureIndexes vector of int
             */
            RlSprite(const std::vector<std::string> pathTextures, std::vector<int> textureIndexes);

            /**
             * @brief Set the Position of the sprite
             * 
             * @param x int
             * @param y int
             */
            void setPosition(const int x, const int y);
            /**
             * @brief Set the Position of the sprite
             * 
             * @param positions pair of int
             */
            void setPosition(std::pair<int, int> positions);
            /**
             * @brief Set the Textures of the sprite
             * 
             * @param pathTextures vector of string
             * @param textureIndexes vector of int
             */
            void setTextures(const std::vector<std::string> pathTextures, std::vector<int> textureIndexes);
            /**
             * @brief Set the Color of the sprite
             * 
             * @param r int
             * @param g int
             * @param b int
             * @param a int
             * @param textureWithColor vector of int
             */
            void setColor(const int r, const int g, const int b, const int a, std::vector<int> textureWithColor);
            /**
             * @brief Set the Scale of the sprite
             * 
             * @param scale float
             */
            void setScale(const float scale);
            /**
             * @brief Set the Speed of the sprite
             * 
             * @param speed float
             */
            void setSpeed(const float speed);
            /**
             * @brief Set the Rotation of the sprite
             * 
             * @param rotation float
             */
            void setRotation(const float rotation);

            /**
             * @brief Get the Pos of the sprite
             * 
             * @return std::pair<int, int> 
             */
            std::pair<int, int> getPos() const;
            /**
             * @brief Get the Pos X of the sprite
             * 
             * @return int 
             */
            int getPosX() const;
            /**
             * @brief Get the Pos Y of the sprite
             * 
             * @return int 
             */
            int getPosY() const;
            /**
             * @brief Get the Textures To Display of the sprite
             * 
             * @return std::vector<std::any> 
             */
            std::vector<std::any> getTexturesToDisplay() const;
            /**
             * @brief Get the red color of the sprite
             * 
             * @return int 
             */
            int getR() const;
            /**
             * @brief get the green color of the sprite
             * 
             * @return int 
             */
            int getG() const;
            /**
             * @brief Get the blue color of the sprite
             * 
             * @return int 
             */
            int getB() const;
            /**
             * @brief Get the alpha value of the sprite
             * 
             * @return int 
             */
            int getA() const;
            /**
             * @brief Get the Scale of the sprite
             * 
             * @return float 
             */
            float getScale() const;
            /**
             * @brief Get the Speed of the sprite
             * 
             * @return float 
             */
            float getSpeed() const;
            /**
             * @brief Get the Rotation of the sprite
             * 
             * @return float 
             */
            float getRotation() const;

            /**
             * @brief Move the sprite
             * 
             * @param velocity pair of int
             */
            void move(const std::pair<int, int> velocity);
            /**
             * @brief Animate the texture of the sprite
             * 
             */
            void animateTextures(float deltaTime);
        private:
            std::vector<Texture2D> _listTextures;
            std::vector<int> _currentTexture;
            std::vector<int> _textureWithColor;
            std::pair<int, int> _positions;
            Color _color;
            float _scale;
            float _speed;
            float _rotation;
    };
} // namespace Raylib
