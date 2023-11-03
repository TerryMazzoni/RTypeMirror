/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** clientmain
*/

#include "Client.hpp"
#include "Communication.hpp"
#include "Core.hpp"

bool is_running(int flag)
{
    static bool status = true;

    if (flag == 1)
        status = false;
    return (status);
}

Client::UDPClient::UDPClient(const std::string &host, const std::string &port)
    : _io_service(), _socket(_io_service), _id(0), _is_ready(false), _game_started(false),
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

Client::UDPClient::~UDPClient()
{
    _socket.close();
}

void Client::UDPClient::processMessage(const std::string &msg, std::shared_ptr<ECS::Core> core)
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
        _shipsPositions.push_back(*ships);
    }
    else if (header->type == Communication::CommunicationTypes::MISSILES) {
        Communication::MissilesPosition *missiles = reinterpret_cast<Communication::MissilesPosition *>(data);
        _missilesPositions.push_back(*missiles);
    }
    else if (header->type == Communication::CommunicationTypes::COLISION) {
        Communication::Colision *colision = reinterpret_cast<Communication::Colision *>(data);
    }
    else if (header->type == Communication::CommunicationTypes::DELETE) {
        Communication::Delete *del = reinterpret_cast<Communication::Delete *>(data);
        _entitiesToDelete.push_back(del->id);
    }
    else {
        std::cout << "Unknown message" << std::endl;
    }
}

void Client::UDPClient::receiveAsync(std::shared_ptr<ECS::Core> core)
{
    std::vector<char> recv_buffer(1500);
    udp::endpoint sender_endpoint;

    _socket.async_receive_from(
        boost::asio::buffer(recv_buffer), sender_endpoint,
        [this, &recv_buffer, &sender_endpoint, &core](
            const boost::system::error_code &error, std::size_t bytes_received) {
            if (!error && bytes_received > 0) {
                processMessage(std::string(
                                   recv_buffer.begin(), recv_buffer.begin() + bytes_received),
                               core);
            }
            else if (error != boost::asio::error::operation_aborted) {
                std::cerr << "Error on receive: " << error.message()
                          << std::endl;
                this->getIoService().stop();
                is_running(1);
            }
            if (!is_running(0)) {
                std::cout << "[RECEIVE] Client stopped" << std::endl;
                return;
            }
            receiveAsync(core);
        });
    getIoService().run();
}

void Client::UDPClient::run()
{
    unsigned long start, end = 0;
    unsigned long elapsed_seconds = 0;

    while (is_running(0)) {
        start = std::chrono::system_clock::now().time_since_epoch().count();
        if (elapsed_seconds >= 30000000) {
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
            if (_game_started) {
                Communication::Inputs input;

                input.nbrItems = _events.size() > 15 ? 15 : _events.size();
                for (size_t i = 0; i < input.nbrItems; i++) {
                    input.event[i] = (Communication::EventInput)_events[i];
                }
                input.type = Communication::CommunicationTypes::INPUT;
                if (input.nbrItems > 0) {
                    this->send(input);
                }
                _events.clear();
            }
            elapsed_seconds -= 30000000;
        }
        for (int i = 0; i < 10000; i++)
            ;
        end = std::chrono::system_clock::now().time_since_epoch().count();
        elapsed_seconds += (end - start);
    }
    this->getIoService().stop();
}

udp::socket &Client::UDPClient::getSocket()
{
    return _socket;
}

boost::asio::io_service &Client::UDPClient::getIoService()
{
    return _io_service;
}

int Client::UDPClient::getId() const
{
    return _id;
}

bool Client::UDPClient::getIsReady() const
{
    return _is_ready;
}

void Client::UDPClient::setIsReady(bool is_ready)
{
    _is_ready = is_ready;
}

void Client::UDPClient::setEvents(std::vector<EventInput> events)
{
    _events = events;
}

std::vector<Communication::ShipsPosition> Client::UDPClient::getShipsPositions()
{
    std::vector<Communication::ShipsPosition> tmp = _shipsPositions;
    _shipsPositions.clear();
    return tmp;
}

std::vector<Communication::MissilesPosition> Client::UDPClient::getMissilesPositions()
{
    std::vector<Communication::MissilesPosition> tmp = _missilesPositions;
    _missilesPositions.clear();
    return tmp;
}

std::vector<int> Client::UDPClient::getEntitiesToDelete()
{
    std::vector<int> tmp = _entitiesToDelete;
    _entitiesToDelete.clear();
    return tmp;
}
