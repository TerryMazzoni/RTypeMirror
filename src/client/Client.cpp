/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** clientmain
*/

#include "Client.hpp"
#include "ACommunication.hpp"
#include "GenericCommunication.hpp"
#include "NewEnnemiesPosition.hpp"
#include "NewHitBetweenElements.hpp"
#include "NewMatesPosition.hpp"
#include "NewMissilesPosition.hpp"
#include "NewPlayerPosition.hpp"
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>

bool is_running(int flag)
{
    static bool status = true;

    if (flag == 1)
        status = false;
    return (status);
}

Client::Client(const std::string &host, const std::string &port)
    : _io_service(), _socket(_io_service),
      _endpoint(boost::asio::ip::address::from_string(host), std::stoi(port))

{
    try {
        _socket.open(udp::v4());
        _socket.bind(udp::endpoint(udp::v4(), 0));
        _socket.connect(_endpoint);
        _socket.non_blocking(true);
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        _socket.close();
    }
    if (_socket.is_open())
        std::cout << "My adress is " << _socket.local_endpoint().address()
                  << ":" << _socket.local_endpoint().port() << std::endl;
}

Client::~Client()
{
    _socket.close();
}

void Client::send(const std::string &msg)
{
    if (msg.empty())
        return;
    _socket.async_send_to(
        boost::asio::buffer(msg, msg.size()), _endpoint,
        [](const boost::system::error_code &error, std::size_t bytes_sent) {
            if (!error && bytes_sent > 0)
                std::cout << "Message sent" << std::endl;
            else
                std::cerr << "Error on send: " << error.message() << std::endl;
        });
}

void Client::processMessage(const std::string &msg)
{
    if (msg != "")
        std::cout << "Received from server: \"" << msg << "\"" << std::endl;
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
        if (msg == "quit") {
            this->getIoService().stop();
            is_running(1);
        }
    }
}

void Client::receiveAsync()
{
    std::vector<char> recv_buffer(1024);

    udp::endpoint sender_endpoint;

    _socket.async_receive_from(
        boost::asio::buffer(recv_buffer), sender_endpoint,
        [this, &recv_buffer, &sender_endpoint](
            const boost::system::error_code &error, std::size_t bytes_received) {
            if (!error && bytes_received > 0) {
                processMessage(std::string(
                    recv_buffer.begin(), recv_buffer.begin() + bytes_received));
            }
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

udp::socket &Client::getSocket()
{
    return _socket;
}

boost::asio::io_service &Client::getIoService()
{
    return _io_service;
}
