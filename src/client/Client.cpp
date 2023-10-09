/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** clientmain
*/

#include "Client.hpp"
#include "Communication.hpp"

bool is_running(int flag)
{
    static bool status = true;

    if (flag == 1)
        status = false;
    return (status);
}

Client::Client(const std::string &host, const std::string &port)
    : _io_service(), _socket(_io_service), _id(0), _is_ready(true), _game_started(false),
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

void Client::processMessage(const std::string &msg)
{
    char *data = const_cast<char *>(msg.c_str());
    Communication::Header *header = reinterpret_cast<Communication::Header *>(data);

    if (header->type == Communication::CommunicationTypes::ID) {
        Communication::Id *id = reinterpret_cast<Communication::Id *>(data);
        _id = id->id;
        if (_id <= 0 || _id > 4) {
            std::cout << "Invalid ID or not enough places remaining" << std::endl;
            is_running(1);
            return;
        }
        std::cout << "My ID is " << _id << std::endl;
    }
    else if (header->type == Communication::CommunicationTypes::QUIT) {
        this->getIoService().stop();
        is_running(1);
    }
    else if (header->type == Communication::CommunicationTypes::TIMER) {
        Communication::Timer *timer = reinterpret_cast<Communication::Timer *>(data);
        static int lastTimer = 0;
        if (timer->time != lastTimer && !_game_started)
            std::cout << "Timer: " << timer->time << std::endl;
        if (timer->time == 0)
            _game_started = true;
        lastTimer = timer->time;
    }
    else if (header->type == Communication::CommunicationTypes::READY) {
        Communication::Ready *ready = reinterpret_cast<Communication::Ready *>(data);
        if (ready->is_ready)
            std::cout << "Ready" << std::endl;
        else
            std::cout << "Not ready" << std::endl;
    }
    else if (header->type == Communication::CommunicationTypes::SHIPS) {
        Communication::ShipsPosition *ships = reinterpret_cast<Communication::ShipsPosition *>(data);
        std::cout << "Ships: " << ships->nbrItems << std::endl;
        for (int i = 0; i < ships->nbrItems; i++) {
            std::cout << "Ship " << i << ": " << std::endl;
            std::cout << "ID: " << ships->ship[i].id << std::endl;
            std::cout << "Life: " << ships->ship[i].life << std::endl;
            std::cout << "Level: " << ships->ship[i].level << std::endl;
            std::cout << "Type: " << static_cast<int>(ships->ship[i].type) << std::endl;
            std::cout << "Position: " << std::endl;
            std::cout << "       X: " << ships->ship[i].position.x << std::endl;
            std::cout << "       Y: " << ships->ship[i].position.y << std::endl;
        }
    }
    else if (header->type == Communication::CommunicationTypes::MISSILES) {
        Communication::MissilesPosition *missiles = reinterpret_cast<Communication::MissilesPosition *>(data);
        std::cout << "Missiles: " << missiles->nbrItems << std::endl;
        for (int i = 0; i < missiles->nbrItems; i++) {
            std::cout << "Missile " << i << ": " << std::endl;
            std::cout << "ID: " << missiles->missile[i].id << std::endl;
            std::cout << "Position: " << std::endl;
            std::cout << "X: " << missiles->missile[i].position.x << std::endl;
            std::cout << "Y: " << missiles->missile[i].position.y << std::endl;
        }
    }
    else if (header->type == Communication::CommunicationTypes::COLISION) {
        Communication::Colision *colision = reinterpret_cast<Communication::Colision *>(data);
        std::cout << "Colisions between: " << colision->id1 << " and " << colision->id2 << std::endl;
    }
    else {
        std::cout << "Unknown message" << std::endl;
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
                Communication::Input input;
                input.nbrItems = 1;
                input.event[0] = Communication::EventInput::Key_up;
                input.type = Communication::CommunicationTypes::INPUT;
                this->send(input);
                if (this->getId() == 0) {
                    Communication::Id id;
                    this->send(id);
                }
                if (this->getIsReady()) {
                    Communication::Ready ready;
                    ready.is_ready = true;
                    this->send(ready);
                }
                else {
                    Communication::Ready ready;
                    ready.is_ready = false;
                    this->send(ready);
                }
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
