/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** ACommunication
*/

#pragma once

#include <string>

enum class CommunicationTypes {
    Type_Unknown,
    Type_NewPlayerPosition,
    Type_NewEnnemiesPosition,
    Type_NewMissilesPosition,
    Type_NewMatesPosition,
    Type_NewHitBetweenElements,
    Type_NewMap
};

class ACommunication {
    public:
        ACommunication()
            : _type(CommunicationTypes::Type_Unknown), _code(0)
        {
        }
        virtual ~ACommunication() = default;
        virtual CommunicationTypes getType() const
        {
            return _type;
        }
        template <class Archive>
        void serialize(Archive &ar, const unsigned int version)
        {
            (void)version;
            ar & _type;
            ar & _code;
        }

    protected:
        ACommunication(CommunicationTypes type, int code)
            : _type(type), _code(code)
        {
        }
        CommunicationTypes _type;
        int _code;
};
