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

bool is_running(int flag)
{
    static bool status = true;

    if (flag == 1)
        status = false;
    return (status);
}

Client::Client(const std::string &host, const std::string &port)
    : _io_service(), _socket(_io_service), _id(0), _is_ready(false),
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

// void Client::send(std::any &data)
// {
//     _socket.send(boost::asio::buffer(&data, sizeof(data)));
// }

void Client::processMessage(const std::string &msg)
{
    if (msg == "quit") {
        this->getIoService().stop();
        is_running(1);
    }
    else if (msg.rfind("ID=", 0) == 0) {
        std::string idStr = msg.substr(3);
        if (idStr.find_first_not_of("0123456789") != std::string::npos)
            return;
        _id = std::stoi(idStr);
        if (_id <= 0 || _id > 4) {
            std::cout << "Invalid ID or not enough places remaining" << std::endl;
            is_running(1);
            return;
        }
        std::cout << "My ID is " << _id << std::endl;
    }
    else if (msg.rfind("TIMER:", 0) == 0) {
        static std::string lastTimer = "";
        std::string timerStr = msg.substr(6);
        if (timerStr.find_first_not_of("0123456789") != std::string::npos)
            return;
        if (timerStr != lastTimer)
            std::cout << "Timer: " << timerStr << std::endl;
        lastTimer = timerStr;
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

void Client::run()
{
    boost::posix_time::milliseconds ms(500);
    boost::asio::deadline_timer t(getIoService(), ms);

    if (!is_running(0))
        return;
    t.expires_at(t.expires_at() + ms);
    t.async_wait(
        [this](const boost::system::error_code &error) {
            if (!error) {
                // if (this->getId() == 0)
                //     this->send("Connect");
                // if (this->getIsReady())
                //     this->send("Ready");
                // else
                //     this->send("Not ready");
            }
            if (!is_running(0))
                return;
            this->run();
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

int Client::getId() const
{
    return _id;
}

bool Client::getIsReady() const
{
    return _is_ready;
}

void Client::setIsReady(bool is_ready)
{
    _is_ready = is_ready;
}
