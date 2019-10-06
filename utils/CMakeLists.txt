project(utils)

if (WIN32)
    include_directories(
        "C:/Boost/include/boost-1_70"
        ./include
    )
    set(CMAKE_CXX_FLAGS "-D_WIN32_WINNT=0x0601 /EHsc")
else ()
    include_directories(./include)
endif ()

add_library(utils
    STATIC
    ./srcs/Packet.cpp
)

if (WIN32)
    target_include_directories(utils INTERFACE
        "C:/Boost/include/boost-1_70"
        ./include
    )
else ()
    target_include_directories(utils INTERFACE
        ./include
    )
endif ()

SET_TARGET_PROPERTIES(utils PROPERTIES LINKER_LANGUAGE CXX)

# add_subdirectory(tests)
