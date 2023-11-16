cmake_minimum_required(VERSION 3.5)
project(handmade-cg VERSION 0.1 LANGUAGES CXX)

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bins)
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")


file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS "lib/*.hpp" "lib/*.cpp" )

include_directories(${CMAKE_SOURCE_DIR}/lib/)

add_library(CommonLib
    ${LIB_SOURCES}
)

function(add_executable_custom _target _sources)
    add_executable(${_target} ${_sources})

    target_link_libraries(${_target} CommonLib SDL2::SDL2)

    add_custom_target(run_${_target}
        COMMAND ./${_target}
        DEPENDS ${_target}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bins
    )
endfunction()

add_executable_custom(algebrick_test programs/algebrick_test/src/main.cpp)
add_executable_custom(graphite_test programs/graphite_test/src/main.cpp)
add_executable_custom(shadow_test programs/shadow_test/src/main.cpp)
add_executable_custom(sphere_test programs/sphere_test/src/main.cpp)
add_executable_custom(ball_plane programs/ball_plane/src/main.cpp)
add_executable_custom(semi-snow programs/semi-snow/src/main.cpp)
add_executable_custom(room programs/room/src/main.cpp)
