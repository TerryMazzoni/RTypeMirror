/*
** EPITECH PROJECT, 2023
** POC-Asio
** File description:
** client
*/

#pragma once

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include "Communication.hpp"

using boost::asio::ip::udp;

bool is_running(int flag);

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
         * @param data The struct to send
         */
        template <typename T>
        void send(T &data)
        {
            try {
                _socket.send(boost::asio::buffer(&data, sizeof(data)));
            }
            catch (const std::exception &e) {
                is_running(1);
                std::cout << "Error on send" << std::endl;
            }
        }
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
        bool _game_started;
};
