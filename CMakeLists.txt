project(Babel)
set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 2.8.12)
add_definitions("-fPIC")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(audio)
# add_subdirectory(database)
add_subdirectory(encoder)
add_subdirectory(network)
add_subdirectory(client_interface)
add_subdirectory(utils)
