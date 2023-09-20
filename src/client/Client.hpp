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
     * @param io_service
     * @param host
     * @param port
     */
    Client(boost::asio::io_service& io_service, const std::string& host,
           const std::string& port);
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
     *
     * @return std::string
     */
    std::string receive();
    /**
     * @brief Process a message from the server
     *
     * @param msg
     */
    void processMessage(const std::string& msg);
    /**
     * @brief Run the client
     */
    void run();
    /**
     * @brief Get the Socket object
     *
     * @return udp::socket&
     */
    udp::socket& getSocket();

private:
    boost::asio::io_service& _io_service;
    udp::socket _socket;
    udp::endpoint _endpoint;
};

bool is_running(int flag);
