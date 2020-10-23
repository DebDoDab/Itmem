cmake_minimum_required(VERSION 3.17)
project(lab2_test)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab2_test test.cpp system_info.cpp ps.h ps.cpp)