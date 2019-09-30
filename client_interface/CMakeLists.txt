include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Qt5Widgets CONFIG REQUIRED)

include_directories(${CMAKE_INCLUDE_PATH})

add_executable(interface
    ./main.cpp
)

target_link_libraries(interface
    # ${CONAN_LIBS}
    Qt5::Widgets
)
set_target_properties(interface PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")