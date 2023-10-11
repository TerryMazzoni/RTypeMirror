/*
** EPITECH PROJECT, 2023
** POC-Asio
** File description:
** server
*/

#include "Args.hpp"
#include "Game.hpp"
#include "Server.hpp"
#include <signal.h>
#include <thread>
#include "Parser.hpp"

std::shared_ptr<Server> server_memory(int flag, std::shared_ptr<Server> server)
{
    static std::shared_ptr<Server> server_memory = nullptr;

    if (flag == 1)
        server_memory = server;
    return (server_memory);
}

static void signal_handler(int signal)
{
    if (signal == SIGINT) {
        is_running(1);
        std::shared_ptr<Server> server = server_memory(0, nullptr);
        server->close();
    }
}

int main(int ac, char **av)
{
    Args args;
    std::shared_ptr<Server> server;
    std::thread receiveThread;
    std::thread runThread;
    std::shared_ptr<Game> game = std::make_shared<Game>();
    std::vector<Parser::entity_t> players = {};
    unsigned long start, end = 0;
    unsigned long elapsed_seconds = 0;

    if (int r = args.setArgs(ac, av) != 0)
        return r - 1;
    server = std::make_shared<Server>(args.getPort());
    server_memory(1, server);
    signal(SIGINT, signal_handler);
    receiveThread = std::thread([&server]() { server->receiveAsync(); });
    runThread = std::thread([&game, &server]() { game->run(server); });
    while (is_running(0)) {
        start = std::chrono::system_clock::now().time_since_epoch().count();
        if (elapsed_seconds >= 100000000) {
            game->updateGame(server);
            elapsed_seconds -= 100000000;
        }
        for (int i = 0; i < 10000; i++)
            ;
        end = std::chrono::system_clock::now().time_since_epoch().count();
        elapsed_seconds += (end - start);
    }
    receiveThread.join();
    runThread.join();
    return 0;
}
