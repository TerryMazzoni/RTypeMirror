/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Position
*/

#pragma once

struct Coords {
    int x;
    int y;
};

class Position {
    public:
        Position();
        ~Position() = default;
        Coords getCoords() { return _coords; };
        Coords getPreviousCoords() { return _previous_coords; };
    protected:
    private:
        Coords _coords;
        Coords _previous_coords;
};
