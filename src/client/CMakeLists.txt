cmake_minimum_required(VERSION 3.0.0)
project(r-type_client)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-Wall -Wextra -fno-gnu-unique)
    
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../)

add_executable(r-type_client
    Args.cpp
    main.cpp
    Client.cpp
)

target_include_directories(r-type_client
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../communication/
)

find_library(SERIALIZATION boost_serialization)
find_library(THREAD pthread)

target_link_libraries(r-type_client PUBLIC ${SERIALIZATION} ${THREAD})