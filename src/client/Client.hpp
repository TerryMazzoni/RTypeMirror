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
    /**
     * @brief Construct a new Client object
     *
     * @param host
     * @param port
     */
    Client(const std::string& host, const std::string& port);
    /**
     * @brief Destroy the Client object
     */
    ~Client();
    /**
     * @brief Send a message to the server
     *
     * @param msg
     */
    void send(const std::string& msg);
    /**
     * @brief Receive a message from the server
     */
    void receiveAsync();
    /**
     * @brief Process a message from the server
     *
     * @param msg
     */
    void processMessage(const std::string& msg);
    /**
     * @brief Get the Socket object
     *
     * @return udp::socket&
     */
    udp::socket& getSocket();
    /**
     * @brief Get the Io Service object
     *
     * @return boost::asio::io_service&
     */
    boost::asio::io_service& getIoService();

private:
    boost::asio::io_service _io_service;
    udp::socket _socket;
    udp::endpoint _endpoint;
};

bool is_running(int flag);
