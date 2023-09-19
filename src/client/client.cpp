/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** clientmain
*/

#include "client.hpp"

bool is_running(int flag)
{
    static bool status = true;

    if (flag == 1)
        status = false;
    return (status);
}

Client::Client(boost::asio::io_service& io_service, const std::string& host,
               const std::string& port)
    : _io_service(io_service), _socket(io_service, udp::endpoint(udp::v4(), 0))
{
    udp::resolver resolver(_io_service);
    try
    {
        _endpoint = *resolver.resolve({udp::v4(), host, port});
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    _socket.non_blocking(true);
    std::cout << "My adress is " << _socket.local_endpoint().address() << ":"
              << _socket.local_endpoint().port() << std::endl;
}

Client::~Client()
{
    _socket.close();
}

void Client::send(const std::string& msg)
{
    _socket.send_to(boost::asio::buffer(msg, msg.size()), _endpoint);
}

std::string Client::receive()
{
    boost::array<char, 1024> recv_buffer;
    udp::endpoint sender_endpoint;

    boost::system::error_code error;
    std::size_t bytes_received = _socket.receive_from(
        boost::asio::buffer(recv_buffer), sender_endpoint, 0, error);

    if (!error)
    {
        return std::string(recv_buffer.data(), bytes_received);
    }
    else if (error == boost::asio::error::would_block)
    {
        // Aucune données disponible
        return "";
    }
    else
    {
        std::cerr << "Error: " << error.message() << std::endl;
        return "";
    }
}

void Client::processMessage(const std::string& msg)
{
    if (msg != "")
        std::cout << "Received from server: " << msg << std::endl;
    if (msg == "quit")
    {
        is_running(1);
    }
}

void Client::run()
{
    while (is_running(0))
    {
        processMessage(receive());
    }
}
