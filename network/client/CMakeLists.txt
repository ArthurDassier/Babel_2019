project(client)

include_directories(
    ./include
    ${CMAKE_INCLUDE_PATH}
)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCES
    ./srcs/sond.cpp
    ./srcs/Client.cpp
)

set(MOC_HEADERS
    ./include/Client.hpp
)

find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Network CONFIG REQUIRED)

add_definitions(${QT_DEFINITIONS})
include_directories(${CMAKE_BINARY_DIR})

QT5_WRAP_CPP(moc_manager ${MOC_HEADERS})

add_executable(babel_client
    ./srcs/sond.cpp
    ./srcs/Client.cpp
    ${moc_manager}
)

target_link_libraries(babel_client
    Qt5::Widgets
    Qt5::Network
    audio
)

set_target_properties(babel_client PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")