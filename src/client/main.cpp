/*
** EPITECH PROJECT, 2023
** POC-Asio
** File description:
** client
*/

#include "ACommunication.hpp"
#include "Args.hpp"
#include "Client.hpp"
#include "GenericCommunication.hpp"
#include "NewPlayerPosition.hpp"
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <signal.h>
#include <sstream>
#include <thread>
#include <any>

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
    // client_memory(0, nullptr)->send("quit\0");
    exit(1);
}

int main(int ac, char **av)
{
    Args args;
    std::shared_ptr<Client> client;
    std::shared_ptr<std::thread> receiveThread;
    std::shared_ptr<std::thread> runThread;

    if (int r = args.setArgs(ac, av) != 0)
        return r - 1;
    client =
        std::make_shared<Client>(args.getIp(), std::to_string(args.getPort()));
    if (!client->getSocket().is_open())
        return 84;
    client_memory(1, client);
    signal(SIGINT, signal_handler);

    GenericCom data = {16, "Connect"};
    Position2 pos = {16, 32, 63};

    std::cout << "data size: " << sizeof(data) << std::endl;
    std::cout << "pos size: " << sizeof(pos) << std::endl;

    client->send(data);
    client->send(pos);
    receiveThread = std::make_shared<std::thread>([&client]() { client->receiveAsync(); });
    runThread = std::make_shared<std::thread>([&client]() { client->run(); });
    receiveThread->join();
    runThread->join();
    return 0;
}
