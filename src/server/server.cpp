/*
** EPITECH PROJECT, 2023
** POC-Asio
** File description:
** server
*/

#include "server.hpp"

bool is_running(int flag)
{
    static bool status = true;

    if (flag == 1)
        status = false;
    return (status);
}

Server::Server(unsigned short port)
    : socket(io_service, udp::endpoint(udp::v4(), port)), response_message(""),
      signals(io_service, SIGINT)
{
    socket.non_blocking(true);
    std::cout << "Server listening on port " << socket.local_endpoint().port()
              << std::endl;
}

Server::~Server()
{
    close();
}

void Server::run()
{
    std::cout << "Server running" << std::endl;
    while (is_running(0))
    {
        auto [received_message, sender] = receive();
        if (received_message != "")
            processMessage(received_message, sender);
    }
}

void Server::send(const std::string& msg, const udp::endpoint& client)
{
    std::cout << "Sending message: " << msg << " to " << client << std::endl;
    socket.send_to(boost::asio::buffer(msg, msg.size()), client);
}

void Server::sendToAll(const std::string& msg)
{
    for (auto& client : clients)
    {
        socket.send_to(boost::asio::buffer(msg), client);
        std::cout << "Sending message: " << msg << " to " << client
                  << std::endl;
    }
}

void Server::processMessage(const std::string& msg, const udp::endpoint& sender)
{
    std::cout << "Processing message: " << msg << " from " << sender
              << std::endl;
    if (msg == "quit")
    {
        response_message = "quit";
        send(response_message, sender);
        removeClient(sender);
    }
    else if (msg == "close_server")
    {
        response_message = "quit";
        sendToAll(response_message);
        is_running(1);
    }
    else
    {
        response_message = msg;
    }
}

std::pair<std::string, udp::endpoint> Server::receive()
{
    boost::array<char, 1024> recv_buffer;
    udp::endpoint sender_endpoint;
    boost::system::error_code error;
    std::size_t bytes_received = socket.receive_from(
        boost::asio::buffer(recv_buffer), sender_endpoint, 0, error);
    std::string received_message;

    if (!error)
    {
        received_message = std::string(recv_buffer.data(), bytes_received);
        clients.insert(sender_endpoint);
    }
    else if (error == boost::asio::error::would_block)
    {
        // Aucune données disponible
        received_message = "";
    }
    else
    {
        std::cerr << "Error: " << error.message() << std::endl;
        response_message = "";
    }
    return std::make_pair(received_message, sender_endpoint);
}

void Server::addClient(const udp::endpoint& client)
{
    clients.insert(client);
}

void Server::removeClient(const udp::endpoint& client)
{
    clients.erase(client);
}

void Server::close()
{
    std::cout << "Server closing" << std::endl;
    is_running(1);
    sendToAll("quit");
    socket.close();
}
