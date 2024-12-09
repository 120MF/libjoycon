cmake_minimum_required(VERSION 3.30)
project(libjoycon)

set(CMAKE_CXX_STANDARD 20)
option(COMPILE_EXAMPLE "" true)
option(JOYCON_SIDE "" "left")

add_library(libjoycon src/Device.cpp src/Device.hpp
        src/utils.hpp)

if (${JOYCON_SIDE} EQUAL "right")
    add_definitions(-DJOYCON_RIGHT)
else ()
    add_definitions(-DJOYCON_LEFT)
endif ()
if (COMPILE_EXAMPLE)
    add_executable(example main.cpp)
    include_directories(src)
    target_link_libraries(example libjoycon)
endif ()