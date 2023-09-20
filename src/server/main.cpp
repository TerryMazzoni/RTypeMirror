/*
** EPITECH PROJECT, 2023
** POC-Asio
** File description:
** server
*/

#include "Args.hpp"
#include "Server.hpp"

static void signal_handler(int signal)
{
    if (signal == SIGINT)
        is_running(1);
}

int main(int ac, char** av)
{
    Args args;
    Server server;

    if (int r = args.setArgs(ac, av) != 0)
        return r - 1;
    server.setServer(args.getPort());
    signal(SIGINT, signal_handler);
    server.run();
    return 0;
}
