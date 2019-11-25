project(server)

include_directories(
    ./include
    ${CMAKE_INCLUDE_PATH}
)

find_package(*Boost* CONFIG REQUIRED)

add_executable(babel_server
    *./srcs/...*
)

target_link_libraries(babel_server
    *Boost::etc*
)

set_target_properties(babel_server PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")