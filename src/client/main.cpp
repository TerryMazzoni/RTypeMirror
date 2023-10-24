/*
** EPITECH PROJECT, 2023
** POC-Asio
** File description:
** client
*/

#include "Args.hpp"
#include "Client.hpp"
#include <signal.h>
#include <thread>
#include <any>
#include "Communication.hpp"
#include "Core.hpp"

std::shared_ptr<Client> client_memory(int flag, std::shared_ptr<Client> client)
{
    static std::shared_ptr<Client> client_memory = nullptr;

    if (flag == 1)
        client_memory = client;
    return (client_memory);
}

static void signal_handler(int signal)
{
    Communication::Quit quit;

    if (signal == SIGINT)
        is_running(1);
    client_memory(0, nullptr)->send(quit);
}

int main(int ac, char **av)
{
    Args args;
    std::shared_ptr<Client> client;
    std::shared_ptr<std::thread> receiveThread;
    std::shared_ptr<std::thread> runThread;
    ECS::Core core;

    if (int r = args.setArgs(ac, av) != 0)
        return r - 1;
    client = std::make_shared<Client>(args.getIp(), std::to_string(args.getPort()));
    if (!client->getSocket().is_open())
        return 84;
    client_memory(1, client);
    signal(SIGINT, signal_handler);
    receiveThread = std::make_shared<std::thread>([&client, &core]() { client->receiveAsync(core); });
    runThread = std::make_shared<std::thread>([&client]() { client->run(); });
    core.run(client);
    receiveThread->join();
    runThread->join();
    return 0;
}
