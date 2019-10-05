include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(
    ./include
    ${Boost_INCLUDE_DIR}
    ${SQLite3_INCLUDE_DIRS}
)

find_package(Qt5Network CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem regex)
find_package(SQLite3 REQUIRED)

add_executable(babel_client
    ./client/client.cpp
    ./client/Client.cpp
    ./sockets/Sockets.cpp
    ./sockets/TCPSocket.cpp
    ./sockets/UDPSocket.cpp
)

target_link_libraries(babel_client
    utils
    pthread
    Qt5::Network
    # ${Boost_LIBRARIES}
)

add_executable(babel_server
    ./server/server.cpp
    ./server/Server.cpp
    ./server/ServerActions.cpp
    ./server/Socket.cpp
    ./sockets/Sockets.cpp
    ./sockets/TCPSocket.cpp
)

# if (SQLITE3_FOUND)
include_directories(${SQLite3_INCLUDE_DIRS})
target_link_libraries(babel_server
        # LINK_PUBLIC
        utils
        sqlite3
        pthread
        dl
        # ${Boost_LIBRARIES}
        # ${SQLite3_LIBRARIES}
)
target_include_directories(babel_server PRIVATE ${SQLite3_INCLUDE_DIRS})
# endif()

set_target_properties(babel_client PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")
set_target_properties(babel_server PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")