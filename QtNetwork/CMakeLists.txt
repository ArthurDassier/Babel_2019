project(QtNetwork)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(
    ./include
    ${CMAKE_INCLUDE_PATH}
)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCES
    camzer.cpp
    # main.cpp
    QtClient.cpp
)

set(MOC_HEADERS
    ./include/QtClient.hpp
)

# find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Network CONFIG REQUIRED)

# include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})
include_directories(${CMAKE_BINARY_DIR})

QT5_WRAP_CPP(moc_manager ${MOC_HEADERS})

add_executable(qt_client
    camzer.cpp
    ./QtClient.cpp
    # ./main.cpp
    ${moc_manager}
)

target_link_libraries(qt_client
    # Qt5::Widgets
    Qt5::Network
)

set_target_properties(qt_client PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")