/*
** EPITECH PROJECT, 2023
** POC-Asio
** File description:
** server
*/

#include "server.hpp"
#include <signal.h>

static void signal_handler(int signal)
{
    is_running(1);
}

int main()
{
    Server server(8080);

    signal(SIGINT, signal_handler);
    server.run();
    return 0;
}
