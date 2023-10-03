/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Texture
*/

#pragma once

#include "RlTexture.hpp"

namespace ECS {
    struct Texture {
            Texture()
                : textureList() { currentTexture = 0; }
            Texture(std::string path) {
                textureList.push_back(Raylib::RlTexture(path));
                currentTexture = 0;
            }
            Texture(Raylib::RlTexture texture) {
                textureList.push_back(texture);
                currentTexture = 0;
            }

            std::vector<Raylib::RlTexture> textureList;
            int currentTexture;
    };
} // namespace ECS
