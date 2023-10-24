/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlSprite
*/

#pragma once

#include <utility>
#include <any>
#include "raylib.h"
#include "Sprite.hpp"

namespace Raylib {
    class RlSprite : public ECS::Sprite {
        public:
            RlSprite();
            RlSprite(const int x, const int y);
            RlSprite(const std::vector<std::string> pathTextures, std::vector<int> textureIndexes);

            void setPosition(const int x, const int y);
            void setPosition(std::pair<int, int> positions);
            void setTextures(const std::vector<std::string> pathTextures, std::vector<int> textureIndexes);
            void setColor(const int r, const int g, const int b, const int a, std::vector<int> textureWithColor);
            void setScale(const float scale);
            void setRotation(const float rotation);

            std::pair<int, int> getPos() const;
            int getPosX() const;
            int getPosY() const;
            std::vector<std::any> getTexturesToDisplay() const;
            int getR() const;
            int getG() const;
            int getB() const;
            int getA() const;
            float getScale() const;
            float getRotation() const;

            void move(const std::pair<int, int> velocity);
            void animateTextures();
        private:
            std::vector<Texture2D> _listTextures;
            std::vector<int> _currentTexture;
            std::vector<int> _textureWithColor;
            std::pair<int, int> _positions;
            Color _color;
            float _scale;
            float _rotation;

    };
} // namespace Raylib
