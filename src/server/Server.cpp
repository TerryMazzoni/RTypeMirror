/*
** EPITECH PROJECT, 2023
** POC-Asio
** File description:
** server
*/

#include "Server.hpp"
#include "Client.hpp"
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
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
    try {
        _socket.async_send_to(
            boost::asio::buffer(msg.c_str(), strlen(msg.c_str())), client,
            [&msg, &client](const boost::system::error_code &error, std::size_t bytes_sent) {
                if (!error && bytes_sent > 0)
                    std::cout << "Message sent" << std::endl;
                else
                    std::cout << error.message() << std::endl;
            });
    }
    catch (const std::exception &e) {
        std::cout << "Cannot send message: \"" << msg.c_str()
                  << "\" to: " << client.address() << ":" << client.port()
                  << std::endl;
    }
}

void Server::sendToAll(const std::string &msg)
{
    for (auto &client : _clients)
        send(msg, client.getEndpoint());
}

void Server::processMessage(const std::string &msg, const udp::endpoint &client)
{
    bool all_ready = true;

    addClient(client);
    try {
        std::istringstream is(msg);
        boost::archive::binary_iarchive ia(is);
        GenericCommunication generic;
        ia >> generic;

        switch (generic.getType()) {
        case CommunicationTypes::Type_NewPlayerPosition: {
            NewPlayerPosition player;
            player.setPosition(generic.getPosition());
            break;
        }
        case CommunicationTypes::Type_NewEnnemiesPosition: {
            NewEnnemiesPosition ennemies;
            ennemies.setPositions(generic.getPositions());
            break;
        }
        case CommunicationTypes::Type_NewMatesPosition: {
            NewMatesPosition mates;
            mates.setMate(generic.getMatePositions());
            break;
        }
        case CommunicationTypes::Type_NewMissilesPosition: {
            NewMissilesPosition missiles;
            missiles.setMissiles(generic.getMissiles());
            break;
        }
        case CommunicationTypes::Type_NewHitBetweenElements: {
            NewHitBetweenElements hit;
            hit.setFirstColision(generic.getFirstColision());
            hit.setSecondColision(generic.getSecondColision());
            hit.setPositions(generic.getPositions());
            break;
        }
        default:
            break;
        }
    }
    catch (std::exception &e) {
        std::cout << "Processing: \"" << msg << "\"" << std::endl;
        if (msg == "quit") {
            send("quit", client);
            removeClient(client);
            std::cout << "Client disconnected" << std::endl;
        }
        else if (msg == "Connect") {
            int id = 0;
            for (auto &c : _clients) {
                if (c.getEndpoint() == client)
                    id = c.getId();
            }
            send("ID=" + std::to_string(id), client);
        }
        else if (msg == "Ready") {
            for (auto &c : _clients)
                if (c.getEndpoint() == client)
                    c.setIsReady(true);
        }
        else if (msg == "Not ready") {
            for (auto &c : _clients)
                if (c.getEndpoint() == client)
                    c.setIsReady(false);
            _game_status = 0;
        }
        else {
            std::cout << "Unknown command, " << e.what() << std::endl;
        }
        for (auto &c : _clients) {
            if (!c.getIsReady())
                all_ready = false;
        }
        if (all_ready)
            _game_status = 1;
    }
}

void Server::receiveAsync()
{
    std::vector<char> recv_buffer(1024);

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
