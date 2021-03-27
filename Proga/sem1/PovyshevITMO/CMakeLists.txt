cmake_minimum_required(VERSION 3.14)
project(PovyshevITMO C)

set(CMAKE_C_STANDARD 99)

add_executable(PovyshevITMO main.c)

target_link_libraries(PovyshevITMO m)