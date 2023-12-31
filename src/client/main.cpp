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

std::shared_ptr<Client::UDPClient> client_memory(int flag, std::shared_ptr<Client::UDPClient> client)
{
    static std::shared_ptr<Client::UDPClient> client_memory = nullptr;

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
    std::shared_ptr<ECS::Core> core = std::make_shared<ECS::Core>();
    Client::Args args;
    std::shared_ptr<Client::UDPClient> client;
    std::shared_ptr<std::thread> receiveThread;
    std::shared_ptr<std::thread> runThread;
    int status = 0;

    if (int r = args.setArgs(ac, av) != 0)
        return r - 1;
    client = std::make_shared<Client::UDPClient>(args.getIp(), std::to_string(args.getPort()));
    if (!client->getSocket().is_open())
        return 84;
    client_memory(1, client);
    signal(SIGINT, signal_handler);
    receiveThread = std::make_shared<std::thread>([&client, &core]() { client->receiveAsync(core); });
    runThread = std::make_shared<std::thread>([&client]() { client->run(); });
    status = core->run(client);
    receiveThread->join();
    runThread->join();
    return status;
}
