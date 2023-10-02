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

class Client {
    public:
        /**
         * @brief Construct a new Client object
         *
         * @param host
         * @param port
         */
        Client(const std::string &host, const std::string &port);
        /**
         * @brief Destroy the Client object
         */
        ~Client();
        /**
         * @brief Send a message to the server
         *
         * @param msg
         */
        void send(const std::string &msg);
        /**
         * @brief Receive a message from the server
         */
        void receiveAsync();
        /**
         * @brief Process a message from the server
         *
         * @param msg
         */
        void processMessage(const std::string &msg);
        /**
         * @brief Run the client
         */
        void run();
        /**
         * @brief Get the Socket object
         *
         * @return udp::socket&
         */
        udp::socket &getSocket();
        /**
         * @brief Get the Io Service object
         *
         * @return boost::asio::io_service&
         */
        boost::asio::io_service &getIoService();
        /**
         * @brief Get the ID object
         *
         * @return int
         */
        int getId() const;
        /**
         * @brief Set the isReady object
         *
         * @param id
         */
        bool getIsReady() const;
        /**
         * @brief Set the isReady object
         *
         * @param is_ready
         */
        void setIsReady(bool is_ready);

    private:
        boost::asio::io_service _io_service;
        udp::socket _socket;
        udp::endpoint _endpoint;
        int _id;
        bool _is_ready;
};

bool is_running(int flag);
