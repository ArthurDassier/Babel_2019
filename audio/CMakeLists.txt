include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(
    ./include
    ${CMAKE_INCLUDE_PATH}
)

add_library(audio
    STATIC
    ./srcs/PortAudio.cpp
)

target_link_libraries(audio
    ${CONAN_LIBS}
)
target_include_directories(audio INTERFACE
    ./include
)

SET_TARGET_PROPERTIES(audio PROPERTIES LINKER_LANGUAGE CXX)