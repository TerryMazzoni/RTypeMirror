/*
** EPITECH PROJECT, 2023
** POC-Asio
** File description:
** client
*/

#include "Args.hpp"
#include "Client.hpp"
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <signal.h>
#include <sstream>

class Person
{
public:
    Person(std::string name, int age) : _name(name), _age(age)
    {
    }
    Person()
    {
    }
    std::string getName() const
    {
        return _name;
    }
    int getAge() const
    {
        return _age;
    }
    template <class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        (void) version;
        ar& _name;
        ar& _age;
    }

private:
    std::string _name;
    int _age;
};

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
    Person person("John", 42);

    if (int r = args.setArgs(ac, av) != 0)
        return r - 1;
    client =
        std::make_shared<Client>(args.getIp(), std::to_string(args.getPort()));
    if (!client->getSocket().is_open())
        return 84;
    client_memory(1, client);
    signal(SIGINT, signal_handler);
    client->send("Connect");
    client->receiveAsync();
    client->getIoService().run();
    return 0;
}
