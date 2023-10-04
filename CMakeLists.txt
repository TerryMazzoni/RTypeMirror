cmake_minimum_required(VERSION 3.10)

project(r-type)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

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
    # ${CLIENT_PATH}/Args.cpp
    # ${CLIENT_PATH}/Client.cpp
    ${CLIENT_PATH}/main.cpp
    ${CLIENT_PATH}/ECS/Core.cpp
    ${CLIENT_PATH}/ECS/EntitiesManager.cpp
    ${CLIENT_PATH}/ECS/Entity.cpp
    ${CLIENT_PATH}/ECS/EventManager.cpp
    ${CLIENT_PATH}/ECS/Factory.cpp
    ${CLIENT_PATH}/ECS/Graph.cpp
    ${CLIENT_PATH}/ECS/SystemManager.cpp
    ${CLIENT_PATH}/ECS/components/Component.cpp
    ${CLIENT_PATH}/ECS/systems/ASystem.cpp
    ${CLIENT_PATH}/ECS/systems/Mouvement.cpp
    ${CLIENT_PATH}/Raylib/RlAudio.cpp
    ${CLIENT_PATH}/Raylib/RlColor.cpp
    ${CLIENT_PATH}/Raylib/RlDraw.cpp
    ${CLIENT_PATH}/Raylib/RlFont.cpp
    ${CLIENT_PATH}/Raylib/RlInputs.cpp
    ${CLIENT_PATH}/Raylib/RlScreen.cpp
    ${CLIENT_PATH}/Raylib/RlSound.cpp
    ${CLIENT_PATH}/Raylib/RlText.cpp
    ${CLIENT_PATH}/Raylib/RlTexture.cpp
    ${CLIENT_PATH}/Raylib/RlWindow.cpp
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
        ${CMAKE_CURRENT_SOURCE_DIR}/src/
        ${CLIENT_PATH}/Raylib/
        ${CLIENT_PATH}/ECS/systems/
        ${CLIENT_PATH}/ECS/components/
        ${CLIENT_PATH}/ECS/
        ${CLIENT_PATH}/ 
)

find_library(SERIALIZATION boost_serialization)
find_library(THREAD pthread)
find_library(RAYLIB raylib)

target_link_libraries(r-type_server PUBLIC ${SERIALIZATION} ${THREAD})
target_link_libraries(r-type_client PUBLIC ${SERIALIZATION} ${THREAD} ${RAYLIB})