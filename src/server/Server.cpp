/*
** EPITECH PROJECT, 2023
** POC-Asio
** File description:
** server
*/

#include "Server.hpp"
#include "Client.hpp"
#include <memory>

bool is_running(int flag)
{
    static bool status = true;

    if (flag == 1)
        status = false;
    return (status);
}

Server::Server(int port)
    : _io_service(), _socket(_io_service), _game_status(0)
{
    _ids[1] = false;
    _ids[2] = false;
    _ids[3] = false;
    _ids[4] = false;
    _socket.open(udp::v4());
    _socket.bind(udp::endpoint(udp::v4(), port));
    _socket.non_blocking(true);
    std::cout << "Server listening on " << _socket.local_endpoint().port() << std::endl;
}

Server::~Server()
{
}

void Server::send(const std::string &msg, const udp::endpoint &client)
{
    if (msg.empty())
        return;
    _socket.async_send_to(
        boost::asio::buffer(msg.c_str(), strlen(msg.c_str())), client,
        [&msg, &client](const boost::system::error_code &error, std::size_t bytes_sent) {
            if (error)
                std::cerr << "Error on send: " << error.message() << std::endl;
            else if (bytes_sent <= 0)
                std::cerr << "Error on send: bytes_sent <= 0" << std::endl;
        });
}

void Server::sendToAll(const std::string &msg)
{
    for (auto &client : _clients)
        send(msg, client.getEndpoint());
}

void Server::processMessage(const std::string &msg, const udp::endpoint &client)
{
    char *data = const_cast<char *>(msg.c_str());
    try {
        Position2 pos = *reinterpret_cast<Position2 *>(data);
        std::cout << "x= " << pos.x << " y= " << pos.y << std::endl;
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    try {
        GenericCom newCom = *reinterpret_cast<GenericCom *>(data);
        std::cout << "code= " << newCom.code << " msg= " << newCom.msg << std::endl;
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

void Server::receiveAsync()
{
    std::vector<char> recv_buffer(1500);

    udp::endpoint sender_endpoint;

    _socket.async_receive_from(
        boost::asio::buffer(recv_buffer), sender_endpoint,
        [this, &recv_buffer, &sender_endpoint](
            const boost::system::error_code &error, std::size_t bytes_received) {
            std::cout << "bytes_received= " << bytes_received << std::endl;
            if (!error && bytes_received > 0)
                processMessage(std::string(recv_buffer.begin(), recv_buffer.begin() + bytes_received), sender_endpoint);
            else if (error != boost::asio::error::operation_aborted) {
                std::cerr << "Error on receive: " << error.message()
                          << std::endl;
                this->getIoService().stop();
                is_running(1);
            }
            if (!is_running(0))
                return;
            receiveAsync();
        });
    getIoService().run();
}

void Server::addClient(const udp::endpoint &client)
{
    for (auto &c : _clients) {
        if (c.getEndpoint() == client)
            return;
    }
    int id = 0;
    for (auto &i : _ids) {
        if (i.second == false) {
            id = i.first;
            i.second = true;
            break;
        }
    }
    _clients.push_back(Client(client, id));
}

void Server::removeClient(const udp::endpoint &client)
{
    for (auto it = _clients.begin(); it != _clients.end(); it++) {
        if (it->getEndpoint() == client) {
            _ids[it->getId()] = false;
            _clients.erase(it);
            return;
        }
    }
}

void Server::removeAllClients()
{
    sendToAll("quit");
    _clients.clear();
    _ids[1] = false;
    _ids[2] = false;
    _ids[3] = false;
    _ids[4] = false;
}

void Server::close()
{
    std::cout << "Server closing" << std::endl;
    removeAllClients();
    is_running(1);
    _io_service.stop();
    _socket.close();
}

boost::asio::io_service &Server::getIoService()
{
    return _io_service;
}

int Server::getGameStatus() const
{
    return _game_status;
}

void Server::setGameStatus(int status)
{
    _game_status = status;
}
