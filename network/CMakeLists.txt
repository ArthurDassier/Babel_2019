include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(
    ./include
    ${Boost_INCLUDE_DIR}
)

# find_package(Qt5 COMPONENTS QtNetwork REQUIRED)
find_package(Qt5Network CONFIG REQUIRED)
# find_package(Boost 1.70 REQUIRED COMPONENTS filesystem regex PATHS "C:/Boost")
find_package(Boost REQUIRED COMPONENTS filesystem regex)

add_executable(babel_client
    ./client/client.cpp
    ./sockets/Sockets.cpp
    ./sockets/TCPSocket.cpp
    ./sockets/UDPSocket.cpp
)

target_link_libraries(babel_client
    pthread
    Qt5::Network
    # ${Boost_LIBRARIES}
)

add_executable(babel_server
    ./server/server.cpp
    ./server/Server.cpp
    ./server/Socket.cpp
)

# if (Boost_FOUND)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(babel_server ${Boost_LIBRARIES})
# endif()

set_target_properties(babel_client PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")
set_target_properties(babel_server PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")