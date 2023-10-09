# RTypeMirror

The goal of this project is to recreate the [R-Type](https://en.wikipedia.org/wiki/R-Type) game in C++ with a multiplayer mode.

![R-Type](https://upload.wikimedia.org/wikipedia/fr/6/64/R-Type_Logo.png)

There is a server and a client. The server is the game engine and the client provide a graphical interface to play the game.

The server is multi-threaded and can handle multiple games at the same time using UDP with a custom protocol in [Boost::Asio](https://www.boost.org/doc/libs/1_66_0/doc/html/boost_asio.html).

The client displays the game using [Raylib](https://www.raylib.com/). It has his own [ECS engine](https://en.wikipedia.org/wiki/Entity_component_system) who can be used for other projects.

## Getting Started

To create the client and the server, use:

    ./install.sh

### Server

    USAGE: ./r-type_server -p port
            port    is the port number      8080 by default

### Client

    USAGE: ./r-type_client -p port -i ip [-m]
        port    is the port number      8080 by default
        ip      is the ip of the server; localhost by default
        m       if present, mute the gui

Made by: Antonin Laudon - Luca Deltort - Terry Mazzoni - Christopher Artigas - Tom Laiolo