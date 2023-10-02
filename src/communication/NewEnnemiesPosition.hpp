/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** NewEnnemiesPosition
*/

#pragma once

#include "Position.hpp"
#include "ACommunication.hpp"
#include <vector>

class NewEnnemiesPosition : public ACommunication {
    public:
        /**
         * @brief Construct a new New Ennemies Position object
         *
         */
        NewEnnemiesPosition()
        {
            _type = CommunicationTypes::Type_NewEnnemiesPosition;
        };
        /**
         * @brief Construct a new New Ennemies Position object
         *
         * @param position
         */
        NewEnnemiesPosition(std::vector<Position> position)
            : _positions(position)
        {
            _type = CommunicationTypes::Type_NewEnnemiesPosition;
        };
        /**
         * @brief Destroy the New Ennemies Position object
         *
         */
        ~NewEnnemiesPosition() = default;
        /**
         * @brief Get the Type object
         *
         * @return CommunicationTypes
         */
        CommunicationTypes getType() const override
        {
            return _type;
        };
        /**
         * @brief Get the Positions object
         *
         * @return std::vector<Position>
         */
        std::vector<Position> getPositions() const
        {
            return _positions;
        }
        /**
         * @brief Set the Positions object
         *
         * @param positions
         */
        void setPositions(std::vector<Position> positions)
        {
            _positions = positions;
        }
        /**
         * @brief Serialize the object for boost
         *
         * @tparam Archive
         * @param ar
         * @param version
         */
        template <class Archive>
        void serialize(Archive &ar, const unsigned int version)
        {
            (void)version;
            ar & _positions;
            ar & _code;
            ar & _type;
        }

    private:
        std::vector<Position> _positions;
};
