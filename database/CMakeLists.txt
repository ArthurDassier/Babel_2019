include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(
    ./include
    ${SQLite3_INCLUDE_DIRS}
)

find_package(SQLite3 REQUIRED)

add_library(database
    STATIC
    ./srcs/Database.cpp
)

target_link_libraries(
    database
    sqlite3
    pthread
    dl
)

target_include_directories(database PRIVATE ${SQLite3_INCLUDE_DIRS})