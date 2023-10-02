/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Client
*/

#include "Client.hpp"

Client::Client(udp::endpoint endpoint, int id)
{
    _endpoint = endpoint;
    _isReady = false;
    _id = id;
}

Client::~Client()
{
}

bool Client::getIsReady() const
{
    return _isReady;
}

void Client::setIsReady(bool isReady)
{
    _isReady = isReady;
}

int Client::getId() const
{
    return _id;
}

void Client::setId(int id)
{
    _id = id;
}

udp::endpoint Client::getEndpoint() const
{
    return _endpoint;
}
