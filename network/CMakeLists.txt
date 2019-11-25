project(network)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(
    ./include
    ${Boost_INCLUDE_DIR}
    ${SQLite3_INCLUDE_DIRS}
)

find_package(SQLite3 REQUIRED)

add_executable(babel_client
    ./client/client.cpp
    ./client/Client.cpp
    ./sockets/Sockets.cpp
    ./sockets/TCPSocket.cpp
    ./sockets/UDPSocket.cpp
)

target_link_libraries(babel_client
    audio
    encoder
    pthread
    utils
)

add_executable(babel_server
    ./server/server.cpp
    ./server/Server.cpp
    ./server/ServerActions.cpp
    ./server/ServerClient.cpp
    ./server/Socket.cpp
    ./sockets/Sockets.cpp
    ./sockets/TCPSocket.cpp
)

target_link_libraries(babel_server
        database
        utils
        pthread
        dl
)

target_include_directories(babel_server PRIVATE ${SQLite3_INCLUDE_DIRS})

set_target_properties(babel_client PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")
set_target_properties(babel_server PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")