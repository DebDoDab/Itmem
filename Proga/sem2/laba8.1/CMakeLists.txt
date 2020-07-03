cmake_minimum_required(VERSION 3.15)
project(Lab8)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab8 main.cpp small_cube.h cube_sweep.h cube_sweep.cpp cube.h brink.h brink.cpp cube_solver.h cube_solver.cpp cube.cpp small_cube.cpp)
target_link_libraries(Lab8 -lglut -lGL -lGLU)