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
    int z;
};

class Position {
    public:
        Position();
        ~Position() = default;
        Coords getCoords() { return _coords; };
        Coords getPreviousCoords() { return _previous_coords; };
        template <class Archive>
        void serialize(Archive& ar, const unsigned int version) {
            ar & name;
            ar & age;
        }
    protected:
    private:
        Coords _coords;
        Coords _previous_coords;
};
