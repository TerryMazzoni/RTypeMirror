/*
** EPITECH PROJECT, 2023
** POC-Asio
** File description:
** server
*/

#pragma once

#include "ACommunication.hpp"
#include "GenericCommunication.hpp"
#include "NewEnnemiesPosition.hpp"
#include "NewHitBetweenElements.hpp"
#include "NewMatesPosition.hpp"
#include "NewMissilesPosition.hpp"
#include "NewPlayerPosition.hpp"
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>

using boost::asio::ip::udp;

class Server
{
public:
    /**
     * @brief Construct a new Server object
     *
     * @param port
     */
    Server(int port);
    /**
     * @brief Destroy the Server object
     *
     */
    ~Server();
    /**
     * @brief Send a message to a client
     *
     * @param msg
     * @param client
     */
    void send(const std::string& msg, const udp::endpoint& client);
    /**
     * @brief Send a message to all clients
     *
     * @param msg
     */
    void sendToAll(const std::string& msg);
    /**
     * @brief Process a message from a client
     *
     * @param msg
     * @param client
     */
    void processMessage(const std::string& msg, const udp::endpoint& client);
    /**
     * @brief Receive a message from a client
     *
     * @return std::pair<std::string, udp::endpoint>
     */
    void receiveAsync();
    /**
     * @brief Get the Socket object
     *
     * @return udp::socket&
     */
    void addClient(const udp::endpoint& client);
    /**
     * @brief Remove a client
     *
     * @param client
     */
    void removeClient(const udp::endpoint& client);
    /**
     * @brief Remove all clients
     */
    void removeAllClients();
    /**
     * @brief Get the Clients object
     */
    void close();
    /**
     * @brief Get the Io Service object
     *
     * @return boost::asio::io_service&
     */
    boost::asio::io_service& getIoService();

private:
    boost::asio::io_service _io_service;
    udp::socket _socket;
    std::set<udp::endpoint> _clients;
    std::string _response_message;
};

bool is_running(int flag);
