mkdir -p build
cd build
cmake ..
cmake --build . -- -j 3
cd ..
echo "
Done!
Launch with:

./r-type_server
USAGE: ./r-type_server -p port
        port    is the port number      8080 by default

./r-type_client
USAGE: ./r-type_client -p port -i ip [-m]
    port    is the port number      8080 by default
    ip      is the ip of the server; localhost by default
    m       if present, mute the gui
"