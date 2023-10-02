/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Position
*/

#pragma once

struct Coords {
        float x;
        float y;
        template <class Archive>
        void serialize(Archive &ar, const unsigned int version)
        {
            (void)version;
            ar & x;
            ar & y;
        }
};

class Position {
    public:
        /**
         * @brief Construct a new Position object
         *
         */
        Position() = default;
        /**
         * @brief Construct a new Position object
         *
         * @param coords
         * @param previous_coords
         */
        Position(Coords coords, Coords previous_coords)
            : _coords(coords), _previous_coords(previous_coords){};
        /**
         * @brief Destroy the Position object
         *
         */
        ~Position() = default;
        /**
         * @brief Get the Coords object
         *
         * @return Coords
         */
        Coords getCoords()
        {
            return _coords;
        };
        /**
         * @brief Get the Previous Coords object
         *
         * @return Coords
         */
        Coords getPreviousCoords()
        {
            return _previous_coords;
        };
        /**
         * @brief Set the Coords object
         *
         * @param coords
         */
        void setCoords(Coords coords)
        {
            _coords = coords;
        };
        /**
         * @brief Set the Previous Coords object
         *
         * @param coords
         */
        void setPreviousCoords(Coords coords)
        {
            _previous_coords = coords;
        };
        /**
         * @brief
         *
         * @tparam Archive
         * @param ar
         * @param version
         */
        template <class Archive>
        void serialize(Archive &ar, const unsigned int version)
        {
            (void)version;
            ar & _coords;
            ar & _previous_coords;
        }

    private:
        Coords _coords;
        Coords _previous_coords;
};
