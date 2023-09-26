/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Graph
*/

#include "Graph.hpp"
#include "RlInputs.hpp"

std::vector<Input> Graph::getInputs() const
{
    return Raylib::getInputs();
}

int Graph::displayEntities(std::vector<EntityId> entities)
{
    (void)entities;
    return 0;
}

Graph::Graph()
{
}

Graph::~Graph()
{
}
