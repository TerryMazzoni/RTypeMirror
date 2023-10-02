/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** ICommunication
*/

#pragma once

#include <string>

enum class CommunicationTypes {
    NewPlayerPosition
};

class Communication {
    public:
        Communication(int code)
            : _code(code){};
        ~Communication() = default;
        const CommunicationTypes &getType()
        {
            return _type;
        };

    protected:
        CommunicationTypes _type;

    private:
        int _code;
};
