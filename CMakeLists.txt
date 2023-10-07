cmake_minimum_required(VERSION 3.24)

set(CMAKE_VERBOSE_MAKEFILE ON)

project(snake VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(snake ${SRC_FILES})

if(MSVC)
  target_compile_options(snake PRIVATE /W4)
else()
  target_compile_options(snake PRIVATE -Wall -Wextra -Wpedantic)
endif()

target_link_libraries(snake PRIVATE X11 sfml-system sfml-window sfml-audio sfml-graphics)
