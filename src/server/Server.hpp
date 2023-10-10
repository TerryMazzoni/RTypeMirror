/*
** EPITECH PROJECT, 2023
** POC-Asio
** File description:
** server
*/

#pragma once

#include "Client.hpp"
#include "Communication.hpp"
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <vector>
#include <map>

using boost::asio::ip::udp;

class Server {
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
        template <typename T>
        void send(T &data, const udp::endpoint &client)
        {
            std::cout << "sended: " << _socket.send_to(boost::asio::buffer(&data, sizeof(data)), client) << " bytes" << std::endl;
        }
        /**
         * @brief Send a message to all clients
         *
         * @param msg
         */
        template <typename T>
        void sendToAll(T &data)
        {
            for (auto &client : _clients)
                _socket.send_to(boost::asio::buffer(&data, sizeof(data)), client.getEndpoint());
        }
        /**
         * @brief Process a message from a client
         *
         * @param msg
         * @param client
         */
        void processMessage(const std::string &msg, const udp::endpoint &client);
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
        void addClient(const udp::endpoint &client);
        /**
         * @brief Remove a client
         *
         * @param client
         */
        void removeClient(const udp::endpoint &client);
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
        boost::asio::io_service &getIoService();
        /**
         * @brief Know the status of the game
         *
         * @return 0 if the game has not started, 1 if the game is starting, 2 if
         * the game is running
         */
        int getGameStatus() const;
        /**
         * @brief Set the Game Status object
         *
         * @param status
         */
        void setGameStatus(int status);
        /**
         * @brief Get the Input object
         *
         * @return std::vector<Communication::Input>&
         */
        std::vector<std::pair<int, Communication::Inputs>> getInput() const;
        /**
         * @brief Clear the input
         */
        void removeInputAt(int index);

    private:
        boost::asio::io_service _io_service;
        udp::socket _socket;
        std::vector<Client> _clients;
        std::string _response_message;
        int _game_status;
        std::map<int, bool> _ids;
        std::vector<std::pair<int, Communication::Inputs>> _inputs;
};

bool is_running(int flag);
