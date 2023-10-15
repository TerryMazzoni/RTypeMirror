/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Texture
*/

#pragma once

#include <vector>

#include "RlTexture.hpp"

namespace ECS {
    struct Texture {
            Texture()
                : textureList()
            {
                currentTexture = {0};
            }
            Texture(std::string path)
            {
                textureList.push_back(Raylib::RlTexture(path));
                currentTexture = {0};
            }
            Texture(std::vector<std::string> pathList, std::vector<int> textureIndexes = {0})
            {
                for (auto &path : pathList)
                    textureList.push_back(Raylib::RlTexture(path));
                currentTexture = textureIndexes;
            }
            Texture(Raylib::RlTexture texture, std::vector<int> textureIndexes = {0})
            {
                textureList.push_back(texture);
                currentTexture = textureIndexes;
            }

            std::vector<Raylib::RlTexture> textureList;
            std::vector<int> currentTexture;
    };
} // namespace ECS
