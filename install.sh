if ! command -v nproc &>/dev/null; then
    num_threads=4
else
    num_threads=$(nproc)
fi

threads_to_use=$((num_threads - 1))

echo "Using $threads_to_use threads to compile"

mkdir -p build
cd build
cmake ..

if cmake --build . -- -j $threads_to_use; then
    echo "Compilation successful!"
else
    echo "Compilation failed!"
    exit 1
fi

cd ..

echo "
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

exit 0
