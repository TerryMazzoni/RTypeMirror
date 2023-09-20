/*
** EPITECH PROJECT, 2023
** POC-Asio
** File description:
** client
*/

#include "Args.hpp"
#include "Client.hpp"
#include <signal.h>

std::shared_ptr<Client> client_memory(int flag, std::shared_ptr<Client> client)
{
    static std::shared_ptr<Client> client_memory = nullptr;

    if (flag == 1)
        client_memory = client;
    return (client_memory);
}

static void signal_handler(int signal)
{
    if (signal == SIGINT)
        is_running(1);
    client_memory(0, nullptr)->send("quit");
}

int main(int ac, char** av)
{
    Args args;
    boost::asio::io_service io_service;
    std::shared_ptr<Client> client;

    if (int r = args.setArgs(ac, av) != 0)
        return r - 1;
    client = std::make_shared<Client>(io_service, args.getIp(),
                                      std::to_string(args.getPort()));
    if (client->getSocket().is_open() == false)
        return 84;
    client_memory(1, client);
    signal(SIGINT, signal_handler);
    client->receive();
    client->run();
    return 0;
}
