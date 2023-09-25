/*
** EPITECH PROJECT, 2023
** POC-Asio
** File description:
** server
*/

#include "Server.hpp"
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>

class Person
{
public:
    Person(std::string name, int age) : _name(name), _age(age)
    {
    }
    Person()
    {
    }
    std::string getName() const
    {
        return _name;
    }
    int getAge() const
    {
        return _age;
    }
    template <class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        (void) version;
        ar& _name;
        ar& _age;
    }

private:
    std::string _name;
    int _age;
};

bool is_running(int flag)
{
    static bool status = true;

    if (flag == 1)
        status = false;
    return (status);
}

Server::Server(int port) : _io_service(), _socket(_io_service)
{
    _socket.open(udp::v4());
    _socket.bind(udp::endpoint(udp::v4(), port));
    _socket.non_blocking(true);
    std::cout << "Server listening on " << _socket.local_endpoint().port()
              << std::endl;
}

Server::~Server()
{
}

void Server::run()
{
    std::cout << "Server running" << std::endl;
    while (is_running(0))
    {
    }
}

void Server::send(const std::string& msg, const udp::endpoint& client)
{
    try
    {
        _socket.send_to(boost::asio::buffer(msg, msg.size()), client);
        std::cout << "Sending message: \"" << msg.c_str()
                  << "\" to: " << client.address() << ":" << client.port()
                  << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Cannot send message: \"" << msg.c_str()
                  << "\" to: " << client.address() << ":" << client.port()
                  << std::endl;
    }
}

void Server::sendToAll(const std::string& msg)
{
    for (auto& client : _clients)
        send(msg, client);
}

void Server::processMessage(const std::string& msg, const udp::endpoint& client)
{
    std::cout << "Processing: \"" << msg << "\"" << std::endl;
    _clients.insert(client);
    if (msg == "quit")
    {
        send("quit", client);
        removeClient(client);
        std::cout << "Client disconnected" << std::endl;
    }
    else if (msg == "Connect")
    {
        send("ID=" + std::to_string(_clients.size()), client);
    }
    else if (msg == "person")
    {
        std::cout << "Person requested" << std::endl;
        Person person("John", 42);
        std::ostringstream archive_stream;
        boost::archive::binary_oarchive archive(archive_stream);
        archive << person;
        std::string person_serialized = archive_stream.str();
        send(person_serialized, client);
    }
    else
    {
        std::cout << "Message received: " << msg << std::endl;
        send(msg, client);
    }
}

void Server::receiveAsync()
{
    boost::array<char, 1024> recv_buffer;
    udp::endpoint sender_endpoint;

    _socket.async_receive_from(
        boost::asio::buffer(recv_buffer), sender_endpoint,
        [this, &recv_buffer, &sender_endpoint](
            const boost::system::error_code& error, std::size_t bytes_received)
        {
            if (!is_running(0))
                return;
            if (!error && bytes_received > 0)
            {
                std::cout << "Received " << bytes_received << " bytes from "
                          << sender_endpoint.address() << ":"
                          << sender_endpoint.port() << std::endl;
                recv_buffer[bytes_received] = '\0';
                processMessage(std::string(recv_buffer.data()),
                               sender_endpoint);
            }
            else if (error != boost::asio::error::operation_aborted)
            {
                std::cerr << "Error on receive: " << error.message()
                          << std::endl;
                this->getIoService().stop();
                is_running(1);
            }
            receiveAsync();
        });
    getIoService().run();
}

void Server::addClient(const udp::endpoint& client)
{
    _clients.insert(client);
}

void Server::removeClient(const udp::endpoint& client)
{
    _clients.erase(client);
}

void Server::removeAllClients()
{
    sendToAll("quit");
    _clients.clear();
}

void Server::close()
{
    std::cout << "Server closing" << std::endl;
    removeAllClients();
    is_running(1);
    _io_service.stop();
    _socket.close();
}

boost::asio::io_service& Server::getIoService()
{
    return _io_service;
}
