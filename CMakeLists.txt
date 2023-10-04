cmake_minimum_required(VERSION 3.10)

project(r-type)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(SERVER_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/server)

# FIND THE BOOST LIB ( IN r-type-dependencies/boost ) AND ADD IT TO THE PROJECT
set(BOOST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/r-type-dependencies/boost)
set(BOOST_LIBRARYDIR ${CMAKE_CURRENT_SOURCE_DIR}/r-type-dependencies/boost/lib)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.75.0 COMPONENTS system thread serialization REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif()

set(SERVER_SOURCES
    ${SERVER_PATH}/Args.cpp
    ${SERVER_PATH}/main.cpp
    ${SERVER_PATH}/Server.cpp
    ${SERVER_PATH}/Client.cpp
    ${SERVER_PATH}/game/Ship.cpp
    ${SERVER_PATH}/game/Bullet.cpp
    ${SERVER_PATH}/game/Game.cpp
)

set(CLIENT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/client)

set(CLIENT_SOURCES
    ${CLIENT_PATH}/Args.cpp
    ${CLIENT_PATH}/main.cpp
    ${CLIENT_PATH}/Client.cpp
)
add_executable(r-type_server ${SERVER_SOURCES})
add_executable(r-type_client ${CLIENT_SOURCES})

target_include_directories(r-type_server
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/communication/
        ${SERVER_PATH}/game/
        ${SERVER_PATH}/
)

target_include_directories(r-type_client
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/communication/
)

# LINK THE BOOST LIB TO THE PROJECT

target_link_libraries(r-type_server ${Boost_LIBRARIES})
target_link_libraries(r-type_client ${Boost_LIBRARIES})