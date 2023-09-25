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

        std::vector<Input> getInputs() const;
        int displayEntities(std::vector<Entity> entities);

    protected:
    private:
        std::vector<Input> _events;
};

#endif /* !GRAPH_HPP_ */
