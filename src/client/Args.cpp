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
    _ip = "127.0.0.1";
    _mute = false;
}

Args::~Args()
{
}

int Args::getPort() const
{
    return _port;
}

std::string Args::getIp() const
{
    return _ip;
}

void Args::setPort(int port)
{
    _port = port;
}

void Args::setIp(const std::string &ip)
{
    _ip = ip;
}

int Args::setArgs(int ac, char **av)
{
    std::string port = "8080";
    std::string ip = "localhost";

    for (int i = 1; i < ac; ++i) {
        if (std::string(av[i]) == "-h" || std::string(av[i]) == "--help") {
            std::cout << "USAGE: " << av[0] << " -p port -i ip"
                      << std::endl;
            std::cout << "\tport\tis the port number\t8080 by default" << std::endl;
            std::cout << "\tip\tis the ip of the server; localhost by default"
                      << std::endl;
            return 1;
        }
    }
    for (int i = 1; i < ac; ++i) {
        if (std::string(av[i]) == "-p" && i + 1 < ac) {
            port = av[i + 1];
        }
        else if (std::string(av[i]) == "-i" && i + 1 < ac) {
            ip = av[i + 1];
        }
    }
    if (port.empty()) {
        std::cerr << "Erreur : le numéro de port (-p) doit être spécifié."
                  << std::endl;
        return 85;
    }
    try {
        std::stoi(port);
    }
    catch (std::exception &e) {
        std::cerr << "Erreur : le numéro de port doit être un nombre."
                  << std::endl;
        return 85;
    }
    setPort(std::stoi(port));
    setIp(ip);
    if (getPort() < 0 || getPort() > 65535) {
        std::cerr
            << "Erreur : le numéro de port doit être compris entre 0 et 65535."
            << std::endl;
        return 85;
    }
    if (getIp().empty()) {
        std::cerr << "Erreur : l'adresse IP (-i) doit être spécifiée."
                  << std::endl;
        return 85;
    }
    if (getIp() == "localhost")
        setIp("127.0.0.1");
    if (!std::regex_match(getIp(), std::regex("^\\b(?:\\d{1,3}\\.){3}\\d{1,3}\\b$"))) {
        std::cerr << "Erreur : l'adresse IP n'est pas valide." << std::endl;
        return 85;
    }
    return 0;
}

void Args::setMute()
{
    _mute = true;
}

bool Args::getMute() const
{
    return _mute;
}
