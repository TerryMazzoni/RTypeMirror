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

void Server::processMessage(const std::string &msg, const udp::endpoint &client)
{
    char *data = const_cast<char *>(msg.c_str());
    Communication::Header *header = reinterpret_cast<Communication::Header *>(data);
    bool all_ready = true;

    if (!is_running(0))
        return;
    addClient(client);
    if (header->type == Communication::CommunicationTypes::QUIT) {
        removeClient(client);
        return;
    }
    else if (header->type == Communication::CommunicationTypes::ID) {
        Communication::Id id = *reinterpret_cast<Communication::Id *>(data);
        for (auto &c : _clients) {
            if (c.getEndpoint() == client)
                id.id = c.getId();
        }

        send(id, client);
    }
    else if (header->type == Communication::CommunicationTypes::READY) {
        Communication::Ready ready = *reinterpret_cast<Communication::Ready *>(data);
        for (auto &c : _clients)
            if (c.getEndpoint() == client)
                c.setIsReady(ready.is_ready);
        if (!ready.is_ready)
            _game_status = 0;
    }
    else if (header->type == Communication::CommunicationTypes::INPUT) {
        Communication::Inputs input = *reinterpret_cast<Communication::Inputs *>(data);
        for (auto &c : _clients) {
            if (c.getEndpoint() == client)
                _inputs.push_back(std::pair<int, Communication::Inputs>(c.getId(), input));
        }
    }
    for (auto &c : _clients) {
        if (!c.getIsReady())
            all_ready = false;
    }
    if (all_ready && _game_status == 0)
        _game_status = 1;
}

void Server::receiveAsync()
{
    std::vector<char> recv_buffer(1500);

    udp::endpoint sender_endpoint;

    _socket.async_receive_from(
        boost::asio::buffer(recv_buffer), sender_endpoint,
        [this, &recv_buffer, &sender_endpoint](
            const boost::system::error_code &error, std::size_t bytes_received) {
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
    Communication::Quit quit;

    for (auto it = _clients.begin(); it != _clients.end(); it++) {
        if (it->getEndpoint() == client) {
            _ids[it->getId()] = false;
            _clients.erase(it);
            send(quit, client);
            _game_status = 0;
            std::cout << "Client " << client << " removed" << std::endl;
            return;
        }
    }
}

void Server::removeAllClients()
{
    Communication::Quit quit;

    sendToAll(quit);
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

std::vector<std::pair<int, Communication::Inputs>> Server::getInput() const
{
    return _inputs;
}

void Server::clearInput()
{
    _inputs.clear();
}