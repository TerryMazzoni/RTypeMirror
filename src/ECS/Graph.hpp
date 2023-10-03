/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Graph
*/

#pragma once

#include <vector>
#include <tuple>
#include <optional>
#include "Enum.hpp"
#include "Entity.hpp"

class Graph {
    public:
        Graph();
        ~Graph();

        std::vector<Input> getInputs() const;
        int displayEntities(std::vector<ECS::Entity> entities);

    protected:
    private:
        int displayTexture(ECS::Entity &entity);
        int displayText(ECS::Entity &entity);
        std::vector<Input> _events;
};
