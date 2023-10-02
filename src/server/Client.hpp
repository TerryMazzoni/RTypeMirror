/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Client
*/

#pragma once

#include <boost/asio.hpp>

using boost::asio::ip::udp;

class Client
{
public:
    /**
     * @brief Construct a new Client object
     *
     * @param endpoint
     */
    Client(udp::endpoint endpoint, int id);
    /**
     * @brief Destroy the Client object
     */
    ~Client();
    /**
     * @brief Get the isReady object
     *
     * @return bool
     */
    bool getIsReady() const;
    /**
     * @brief Set the isReady object
     *
     * @param isReady
     */
    void setIsReady(bool isReady);
    /**
     * @brief Get the Id object
     *
     * @return int
     */
    int getId() const;
    /**
     * @brief Set the Id object
     *
     * @param id
     */
    void setId(int id);
    /**
     * @brief Get the Endpoint object
     *
     * @return udp::endpoint
     */
    udp::endpoint getEndpoint() const;

private:
    udp::endpoint _endpoint;
    bool _isReady;
    int _id;
};
