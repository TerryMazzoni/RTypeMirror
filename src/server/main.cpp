/*
** EPITECH PROJECT, 2023
** POC-Asio
** File description:
** server
*/

#include "Args.hpp"
#include "Game.hpp"
#include "Server.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <signal.h>
#include <thread>

std::shared_ptr<Server> server_memory(int flag, std::shared_ptr<Server> server)
{
    static std::shared_ptr<Server> server_memory = nullptr;

    if (flag == 1)
        server_memory = server;
    return (server_memory);
}

static void signal_handler(int signal)
{
    if (signal == SIGINT)
    {
        is_running(1);
        std::shared_ptr<Server> server = server_memory(0, nullptr);
        server->close();
    }
}

void test(std::shared_ptr<Server> server)
{
    boost::asio::deadline_timer t(server->getIoService(),
                                  boost::posix_time::milliseconds(1000));
    t.async_wait(
        [&server](const boost::system::error_code& error)
        {
            if (!error)
            {
                std::cout << "1 second" << std::endl;
                server->sendToAll("1 second");
            }
            server->getIoService().post([server]() { test(server); });
        });
    server->getIoService().run();
}

int main(int ac, char** av)
{
    Args args;
    std::shared_ptr<Server> server;
    std::thread receiveThread;
    std::thread runThread;
    std::shared_ptr<Game> game = std::make_shared<Game>();

    if (int r = args.setArgs(ac, av) != 0)
        return r - 1;
    server = std::make_shared<Server>(args.getPort());
    server_memory(1, server);
    signal(SIGINT, signal_handler);
    receiveThread = std::thread([&server]() { server->receiveAsync(); });
    runThread = std::thread([&game, &server]() { game->run(server); });
    receiveThread.join();
    runThread.join();
    return 0;
}
