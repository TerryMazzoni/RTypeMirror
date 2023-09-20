/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Graph
*/

#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <vector>
#include <tuple>
#include <optional>
#include "Enum.hpp"

class Graph {
    public:
        Graph();
        ~Graph();

        std::vector<std::tuple<EventType, int, std::optional<int>>> getInputs() const;
        int displayEntities(std::vector<std::pair<EntityType, int>> entities);

    protected:
    private:
        std::vector<std::tuple<EventType, int, std::optional<int>>> _events;
};

#endif /* !GRAPH_HPP_ */
