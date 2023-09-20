/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlTexture
*/

#pragma once

#include <string>

#include "raylib.h"
#include "RlColor.hpp"

namespace Raylib {
    class RlTexture {
        public:
            RlTexture(std::string path);
            ~RlTexture();

            void draw(int x, int y, RlColor color = RlColor(255, 255, 255));
            void unload();
            int getWidth() const;
            int getHeight() const;
        private:
            Texture2D _texture;
    };
}
