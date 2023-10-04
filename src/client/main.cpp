/*
** EPITECH PROJECT, 2023
** POC-Asio
** File description:
** client
*/

<<<<<<< HEAD
#include "Args.hpp"
#include "Client.hpp"
#include <signal.h>
#include <thread>
#include <any>
#include "Communication.hpp"
=======
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
>>>>>>> 917f3c6 (Add start of refacto, I can send everything)

std::shared_ptr<Client> client_memory(int flag, std::shared_ptr<Client> client)
{
    static std::shared_ptr<Client> client_memory = nullptr;

    if (flag == 1)
        client_memory = client;
    return (client_memory);
}

// static void signal_handler(int signal)
// {
//     if (signal == SIGINT)
//         is_running(1);
//     client_memory(0, nullptr)->send("quit\0");
// }

// int main(int ac, char **av)
// {
//     Args args;
//     std::shared_ptr<Client> client;
//     std::shared_ptr<std::thread> receiveThread;
//     std::shared_ptr<std::thread> runThread;

//     if (int r = args.setArgs(ac, av) != 0)
//         return r - 1;
//     client =
//         std::make_shared<Client>(args.getIp(), std::to_string(args.getPort()));
//     if (!client->getSocket().is_open())
//         return 84;
//     client_memory(1, client);
//     signal(SIGINT, signal_handler);
//     client->send("Connect");

//     GenericCommunication generic(CommunicationTypes::Type_NewPlayerPosition);

//     generic.setPosition(Position(Coords{1, 2}, Coords{3, 4}));
//     generic.setTeam(1);

//     std::ostringstream os;
//     boost::archive::binary_oarchive oa(os);
//     oa << generic;
//     client->send(os.str());
//     client->send("Not ready");
//     receiveThread = std::make_shared<std::thread>([&client]() { client->receiveAsync(); });
//     runThread = std::make_shared<std::thread>([&client]() { client->run(); });
//     receiveThread->join();
//     runThread->join();
//     return 0;
// }

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

    if (int r = args.setArgs(ac, av) != 0)
        return r - 1;
    client =
        std::make_shared<Client>(args.getIp(), std::to_string(args.getPort()));
    if (!client->getSocket().is_open())
        return 84;
    client_memory(1, client);
    signal(SIGINT, signal_handler);
    receiveThread = std::make_shared<std::thread>([&client]() { client->receiveAsync(); });
    runThread = std::make_shared<std::thread>([&client]() { client->run(); });
    receiveThread->join();
    runThread->join();
    return 0;
}
