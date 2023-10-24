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
            virtual void setPosition(const int x, const int y) = 0;
            virtual void setPosition(std::pair<int, int> positions) = 0;
            virtual void setTextures(const std::vector<std::string> pathTextures, std::vector<int> textureIndexes) = 0;
            virtual void setColor(const int r, const int g, const int b, const int a, std::vector<int> textureToApply) = 0;
            virtual void setScale(const float scale) = 0;
            virtual void setRotation(const float rotation) = 0;

            virtual std::pair<int, int> getPos() const = 0;
            virtual int getPosX() const = 0;
            virtual int getPosY() const = 0;
            virtual std::vector<std::any> getTexturesToDisplay() const = 0;
            virtual int getR() const = 0;
            virtual int getG() const = 0;
            virtual int getB() const = 0;
            virtual int getA() const = 0;
            virtual float getScale() const = 0;
            virtual float getRotation() const = 0;

            virtual void move(const std::pair<int, int> velocity) = 0;
            virtual void animateTextures() = 0;
    };
} // namespace ECS
