include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(
    ./include
    ${CMAKE_INCLUDE_PATH}
)

add_library(encoder
    STATIC
    ./srcs/OpusE.cpp
)

target_link_libraries(encoder
    ${CONAN_LIBS}
)
target_include_directories(encoder INTERFACE
    ./include
)

SET_TARGET_PROPERTIES(encoder PROPERTIES LINKER_LANGUAGE CXX)