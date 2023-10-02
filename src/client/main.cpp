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
    client_memory(0, nullptr)->send("quit\0");
}

int main(int ac, char** av)
{
    Args args;
    std::shared_ptr<Client> client;

    if (int r = args.setArgs(ac, av) != 0)
        return r - 1;
    client =
        std::make_shared<Client>(args.getIp(), std::to_string(args.getPort()));
    if (!client->getSocket().is_open())
        return 84;
    client_memory(1, client);
    signal(SIGINT, signal_handler);
    client->send("Connect");

    GenericCommunication generic(CommunicationTypes::Type_NewPlayerPosition);

    generic.setPosition(Position(Coords{1, 2}, Coords{3, 4}));
    generic.setTeam(1);

    std::ostringstream os;
    boost::archive::binary_oarchive oa(os);
    oa << generic;
    client->send(os.str());
    client->receiveAsync();
    client->getIoService().run();
    return 0;
}
