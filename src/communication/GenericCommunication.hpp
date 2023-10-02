/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** GenericCommunication
*/

#pragma once
#include "ACommunication.hpp"
#include "Position.hpp"
#include "NewMatesPosition.hpp"
#include "NewMissilesPosition.hpp"
#include "NewHitBetweenElements.hpp"

class GenericCommunication : public ACommunication {
    public:
        /**
         * @brief Construct a new Generic Communication object
         *
         * @param type
         */
        GenericCommunication(CommunicationTypes type)
        {
            _type = type;
        };
        /**
         * @brief Construct a new Generic Communication object
         *
         */
        GenericCommunication()
        {
            _type = CommunicationTypes::Type_Unknown;
        };
        /**
         * @brief Destroy the Generic Communication object
         *
         */
        ~GenericCommunication() = default;
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
            ar & _code;
            ar & _type;
            ar & _position;
            ar & _positions;
            ar & _first_c;
            ar & _second_c;
            ar & _Matepositions;
            ar & _missiles;
            ar & _team;
        }
        /**
         * @brief Set the Position object
         *
         * @param position
         */
        void setPosition(Position position)
        {
            _position = position;
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
         * @brief Set the First Colision object
         *
         * @param first_c
         */
        void setFirstColision(Colision first_c)
        {
            _first_c = first_c;
        }
        /**
         * @brief Set the Second Colision object
         *
         * @param second_c
         */
        void setSecondColision(Colision second_c)
        {
            _second_c = second_c;
        }
        /**
         * @brief Set the Mate Positions object
         *
         * @param Matepositions
         */
        void setMatePositions(std::vector<Mate> Matepositions)
        {
            _Matepositions = Matepositions;
        }
        /**
         * @brief Set the Missiles object
         *
         * @param missiles
         */
        void setMissiles(std::vector<Missile> missiles)
        {
            _missiles = missiles;
        }
        /**
         * @brief Set the Team object
         *
         * @param team
         */
        void setTeam(int team)
        {
            _team = team;
        }

        /**
         * @brief Get the Position object
         *
         * @return Position
         */
        Position getPosition() const
        {
            return _position;
        }
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
         * @brief Get the First Colision object
         *
         * @return std::pair<ColisionTypes, int>
         */
        Colision getFirstColision() const
        {
            return _first_c;
        }
        /**
         * @brief Get the Second Colision object
         *
         * @return std::pair<ColisionTypes, int>
         */
        Colision getSecondColision() const
        {
            return _second_c;
        }
        /**
         * @brief Get the Mate Positions object
         *
         * @return Mate
         */
        std::vector<Mate> getMatePositions() const
        {
            return _Matepositions;
        }
        /**
         * @brief Get the Missiles object
         *
         * @return std::vector<Missile>
         */
        std::vector<Missile> getMissiles() const
        {
            return _missiles;
        }
        /**
         * @brief Get the Team object
         *
         * @return int
         */
        int getTeam() const
        {
            return _team;
        }

    private:
        Position _position;
        std::vector<Position> _positions;
        Colision _first_c;
        Colision _second_c;
        std::vector<Mate> _Matepositions;
        std::vector<Missile> _missiles;
        int _team;
};
