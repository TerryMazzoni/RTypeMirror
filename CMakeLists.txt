cmake_minimum_required(VERSION 3.10)

project(r-type)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake"
                "${CMAKE_BINARY_DIR}/conan.cmake"
                TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_configure(REQUIRES boost/1.83.0
                      GENERATORS cmake)

conan_cmake_autodetect(settings)

conan_cmake_install(PATH_OR_REFERENCE .
                    BUILD missing
                    REMOTE conancenter)

include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(SERVER_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/server)

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

find_library(SERIALIZATION boost_serialization)
find_library(THREAD pthread)

target_link_libraries(r-type_server PUBLIC CONAN_PKG::boost_serialization CONAN_PKG::pthreads)
target_link_libraries(r-type_client PUBLIC CONAN_PKG::boost_serialization CONAN_PKG::pthreads)