/*
** EPITECH PROJECT, 2023
** POC-Asio
** File description:
** client
*/

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::udp;

class Client
{
public:
    Client(boost::asio::io_service& io_service, const std::string& host,
           const std::string& port);
    ~Client();
    void send(const std::string& msg);
    std::string receive();
    void processMessage(const std::string& msg);
    void run();

private:
    boost::asio::io_service& _io_service;
    udp::socket _socket;
    udp::endpoint _endpoint;
};

bool is_running(int flag);
