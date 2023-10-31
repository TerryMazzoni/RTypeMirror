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

#include "Enum.hpp"
#include "Communication.hpp"

namespace ECS {
    class Core;
}

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
            catch (...) {
                is_running(1);
                std::cout << "Error on send" << std::endl;
            }
        }
        /**
         * @brief Receive a message from the server
         * 
         * @param ECS::Core
         */
        void receiveAsync(std::shared_ptr<ECS::Core> core);
        /**
         * @brief Process a message from the server
         *
         * @param msg
         */
        void processMessage(const std::string &msg, std::shared_ptr<ECS::Core> core);
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
        /**
         * @brief Set the Events Input for the server
         *
         * @param events
         */
        void setEvents(std::vector<EventInput> events);
        /**
         * @brief Get the Ships Positions object
         * 
         * @return std::vector<Communication::ShipsPosition> 
         */
        std::vector<Communication::ShipsPosition> getShipsPositions();
        /**
         * @brief Get the Missiles Positions object
         * 
         * @return std::vector<Communication::MissilesPosition> 
         */
        std::vector<Communication::MissilesPosition> getMissilesPositions();
        /**
         * @brief Get the Entities id To Delete object
         * 
         * @return std::vector<int> 
         */
        std::vector<int> getEntitiesToDelete();
    private:
        boost::asio::io_service _io_service;
        udp::socket _socket;
        udp::endpoint _endpoint;
        int _id;
        bool _is_ready;
        bool _game_started;
        std::vector<EventInput> _events;
        std::vector<Communication::ShipsPosition> _shipsPositions;
        std::vector<Communication::MissilesPosition> _missilesPositions;
        std::vector<int> _entitiesToDelete;
};
