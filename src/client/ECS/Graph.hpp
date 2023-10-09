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
#include "ECS.hpp"
#include "Raylib.hpp"

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
        int displayEntities(std::vector<ECS::Entity> entities);

    protected:
    private:
        /**
         * @brief Display a texture entity
         * 
         * @param Entity 
         * @return int 
         */
        int displayTexture(ECS::Entity &entity);
        /**
         * @brief Display a text entity
         * 
         * @param Entity 
         * @return int
        */
        int displayText(ECS::Entity &entity);
        std::vector<Input> _events;
};
