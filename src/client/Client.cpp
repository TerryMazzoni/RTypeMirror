/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** clientmain
*/

#include "Client.hpp"
#include "Person.hpp"
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

bool is_running(int flag)
{
    static bool status = true;

    if (flag == 1)
        status = false;
    return (status);
}

Client::Client(const std::string& host, const std::string& port)
    : _io_service(), _socket(_io_service),
      _endpoint(boost::asio::ip::address::from_string(host), std::stoi(port))

{
    try
    {
        _socket.open(udp::v4());
        _socket.bind(udp::endpoint(udp::v4(), 0));
        _socket.connect(_endpoint);
        _socket.non_blocking(true);
    }
    catch (const std::exception& e)
    {
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

void Client::send(const std::string& msg)
{
    _socket.send_to(boost::asio::buffer(msg, msg.size()), _endpoint);
    std::cout << "Sending message: \"" << msg
              << "\" to: " << _endpoint.address() << ":" << _endpoint.port()
              << std::endl;
}

void Client::processMessage(const std::string& msg)
{
    if (msg != "")
        std::cout << "Received from server: \"" << msg << "\"" << std::endl;
    try
    {
        std::istringstream is(msg);
        boost::archive::binary_iarchive ia(is);

        Person person;
        ia >> person;

        std::cout << "Person: " << person.getName() << " " << person.getAge()
                  << std::endl;
    }
    catch (std::exception& e)
    {
        if (msg == "quit")
        {
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
            const boost::system::error_code& error, std::size_t bytes_received)
        {
            if (!is_running(0))
                return;
            if (!error && bytes_received > 0)
            {
                processMessage(std::string(
                    recv_buffer.begin(), recv_buffer.begin() + bytes_received));
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

void Client::run()
{
    send("Hello");
    std::cout << "Hello" << std::endl;
    while (is_running(0))
    {
    }
}

udp::socket& Client::getSocket()
{
    return _socket;
}

boost::asio::io_service& Client::getIoService()
{
    return _io_service;
}
