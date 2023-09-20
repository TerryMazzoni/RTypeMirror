/*
** EPITECH PROJECT, 2023
** POC-Asio
** File description:
** server
*/

#pragma once

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
     */
    Server();
    /**
     * @brief Destroy the Server object
     *
     */
    ~Server();
    /**
     * @brief Set the Server object
     *
     * @param port
     */
    void setServer(int port);
    /**
     * @brief Run the server
     *
     */
    void run();
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
    std::pair<std::string, udp::endpoint> receive();
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
     * @brief Get the Clients object
     */
    void close();

private:
    boost::asio::io_service _io_service;
    udp::socket _socket;
    std::set<udp::endpoint> _clients;
    std::string _response_message;
    boost::asio::signal_set _signals;
};

bool is_running(int flag);
