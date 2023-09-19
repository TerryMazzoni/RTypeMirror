/*
** EPITECH PROJECT, 2023
** POC-Asio
** File description:
** client
*/

#include "client.hpp"
#include <boost/asio.hpp>
#include <iostream>
#include <signal.h>
#include <thread>

std::shared_ptr<Client> client_memory(int flag, std::shared_ptr<Client> client)
{
    static std::shared_ptr<Client> client_memory = nullptr;

    if (flag == 1)
        client_memory = client;
    return (client_memory);
}

static void signal_handler(int signal)
{
    is_running(1);
    client_memory(0, nullptr)->send("quit");
}

int main()
{
    boost::asio::io_service io_service;
    std::shared_ptr<Client> client =
        std::make_shared<Client>(io_service, "127.0.0.1", "8080");

    client_memory(1, client);
    signal(SIGINT, signal_handler);
    client->send("Hello");
    client->run();
    return 0;
}
