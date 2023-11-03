/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Client
*/

#include "Client.hpp"

Server::Client::Client(udp::endpoint endpoint, int id)
{
    _endpoint = endpoint;
    _isReady = false;
    _id = id;
}

Server::Client::~Client()
{
}

bool Server::Client::getIsReady() const
{
    return _isReady;
}

void Server::Client::setIsReady(bool isReady)
{
    _isReady = isReady;
}

int Server::Client::getId() const
{
    return _id;
}

void Server::Client::setId(int id)
{
    _id = id;
}

udp::endpoint Server::Client::getEndpoint() const
{
    return _endpoint;
}
