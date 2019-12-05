project(server)

SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)
FIND_PACKAGE(Boost 1.42.0 REQUIRED COMPONENTS system thread regex)
IF(Boost_FOUND)
  INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
  LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ENDIF(Boost_FOUND)

SET(USED_LIBS
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${Boost_REGEX_LIBRARY}
)

ADD_EXECUTABLE(babel_server
    ./srcs/udp.cpp
)

TARGET_LINK_LIBRARIES(babel_server
    ${USED_LIBS}
    pthread
)

# include_directories(
#     ./include
#     ${CMAKE_INCLUDE_PATH}
#     ${Boost_INCLUDE_DIR}
# )

# find_package(Boost COMPONENTS SYSTEM)

# add_executable(babel_server
#     ./srcs/server.cpp
# )

# target_link_libraries(babel_server
#     ${Boost_LIBRARIES}
# )

set_target_properties(babel_server PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")