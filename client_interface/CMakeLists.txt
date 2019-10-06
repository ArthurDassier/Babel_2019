include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Qt5Widgets CONFIG REQUIRED)

include_directories(
    ./include
    ${CMAKE_INCLUDE_PATH}
)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(MOC_FILES
    ./include/mainwindow.h
)

QT5_WRAP_CPP(moc_manager ${MOC_FILES})

add_executable(interface
    ./main.cpp
    ./mainwindow.cpp
    ${moc_manager}
)

target_link_libraries(interface
    # ${CONAN_LIBS}
    Qt5::Widgets
)
set_target_properties(interface PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")