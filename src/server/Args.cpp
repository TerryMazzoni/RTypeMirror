/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Args
*/

#include "Args.hpp"

Args::Args()
{
    _port = 8080;
}

Args::~Args()
{
}

int Args::getPort() const
{
    return _port;
}

void Args::setPort(int port)
{
    _port = port;
}

int Args::setArgs(int ac, char** av)
{
    std::string port = "8080";

    for (int i = 1; i < ac; ++i)
    {
        if (std::string(av[i]) == "-h" || std::string(av[i]) == "--help")
        {
            std::cout << "USAGE: " << av[0] << " -p port" << std::endl;
            std::cout << "\tport\tis the port number" << std::endl;
            return 1;
        }
    }
    for (int i = 1; i < ac; ++i)
    {
        if (std::string(av[i]) == "-p" && i + 1 < ac)
        {
            port = av[i + 1];
        }
    }
    if (port.empty())
    {
        std::cerr << "Erreur : le numéro de port (-p) doit être spécifié."
                  << std::endl;
        return 85;
    }
    try
    {
        std::stoi(port);
    }
    catch (std::exception& e)
    {
        std::cerr << "Erreur : le numéro de port doit être un nombre."
                  << std::endl;
        return 85;
    }
    setPort(std::stoi(port));
    if (getPort() < 0 || getPort() > 65535)
    {
        std::cerr
            << "Erreur : le numéro de port doit être compris entre 0 et 65535."
            << std::endl;
        return 85;
    }
    return 0;
}
