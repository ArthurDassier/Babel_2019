project(client_interface)

include_directories(
    ./include
    ${CMAKE_BINARY_DIR}
    ${CMAKE_INCLUDE_PATH}
)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCES
    ./srcs/ClientInterface.cpp
    ./srcs/QtInterface.cpp
)

set(MOC_HEADERS
    ./include/ClientInterface.hpp
    ./include/QtInterface.hpp
)

find_package(Qt5Widgets CONFIG REQUIRED)

add_definitions(${QT_DEFINITIONS})

QT5_WRAP_CPP(moc_manager ${MOC_HEADERS})

add_library(interface
    STATIC
    ./srcs/ClientInterface.cpp
    ./srcs/QtInterface.cpp
    ${moc_manager}
)

target_include_directories(interface INTERFACE
    ./include()
)

target_link_libraries(interface
    Qt5::Widgets
)

set_target_properties(interface PROPERTIES LINKER_LANGUAGE CXX)