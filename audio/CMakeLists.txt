include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

include_directories(
    ./include
    ${CMAKE_INCLUDE_PATH}
    # ${SQLite3_INCLUDE_DIRS}
)

add_library(audio
    STATIC
    ./srcs/PortAudio.cpp
)

target_link_libraries(audio
    ${CONAN_LIBS}
    # sqlite3
    # pthread
    # dl
)

# target_include_directories(audio PRIVATE ${SQLite3_INCLUDE_DIRS})