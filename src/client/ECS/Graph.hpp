/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Graph
*/

#pragma once

#include <vector>
#include <set>
#include <tuple>
#include <optional>
#include "Enum.hpp"
#include "Entity.hpp"
#include "Sprite.hpp"
#include "Musics.hpp"
#include "Sounds.hpp"

namespace Graphic {
    class Graph {
        public:
            Graph();
            ~Graph();
            /**
             * @brief Get the Inputs list
             *
             * @return std::set<Input>
             */
            std::set<Input> getInputs() const;
            /**
             * @brief Display the entity vector
             *
             * @param std::vector<Entity>
             * @return int
             */
            int displayEntities(std::vector<std::optional<ECS::Entity>> entities);

        protected:
        private:
            /**
             * @brief Display a texture entity
             *
             * @param Entity
             * @return int
             */
            int displayTexture(ECS::Entity &entity);
            std::vector<Input> _events;
    };
    /**
     * @brief Create a Sprite object
     *
     * @return std::shared_ptr<ECS::Sprite>
     */
    std::shared_ptr<ECS::Sprite> createSprite();
    /**
     * @brief Create a Sprite object
     *
     * @param x pos
     * @param y pos
     * @return std::shared_ptr<ECS::Sprite>
     */
    std::shared_ptr<ECS::Sprite> createSprite(const int x, const int y);
    /**
     * @brief Create a Sprite object
     *
     * @param pathTextures vector
     * @param textureIndexes vector
     * @return std::shared_ptr<ECS::Sprite>
     */
    std::shared_ptr<ECS::Sprite> createSprite(const std::vector<std::string> pathTextures, std::vector<int> textureIndexes);
    /**
     * @brief Create a Musics object
     * 
     * @param path 
     * @return std::shared_ptr<ECS::Musics> 
     */
    std::shared_ptr<ECS::Musics> createMusics(const std::string path);
    /**
     * @brief Create a Sound object
     * 
     * @param path 
     * @return std::shared_ptr<ECS::Musics> 
     */
    std::shared_ptr<ECS::Sounds> createSound(const std::string path);
    /**
     * @brief Create a Window object
     *
     * @param height
     * @param width
     * @param name
     * @param frameRate
     */
    void createWindow(int width, int height, std::string name, int frameRate);
    /**
     * @brief Close the window
     *
     */
    void closeWindow();
    /**
     * @brief Refresh the window
     *
     */
    void refreshWindow();
    /**
     * @brief Check if the window is open
     *
     * @return true
     * @return false
     */
    bool checkWindowOpen();
} // namespace Graphic
