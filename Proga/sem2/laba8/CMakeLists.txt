cmake_minimum_required(VERSION 3.16)
project(laba8)

set(CMAKE_CXX_STANDARD 14)

add_executable(laba8 CubeGL.cpp cube.cpp cube.h smallcube.cpp smallcube.h CubeGL.h )
target_link_libraries(laba8 -lglut -lGL -lGLU)