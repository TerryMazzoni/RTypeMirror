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
    Server(unsigned short port);
    ~Server();
    void run();
    void send(const std::string& msg, const udp::endpoint& client);
    void sendToAll(const std::string& msg);
    void processMessage(const std::string& msg, const udp::endpoint& client);
    std::pair<std::string, udp::endpoint> receive();
    void addClient(const udp::endpoint& client);
    void removeClient(const udp::endpoint& client);
    void close();

private:
    boost::asio::io_service io_service;
    udp::socket socket;
    std::set<udp::endpoint> clients;
    std::string response_message;
    boost::asio::signal_set signals;
};

bool is_running(int flag);
