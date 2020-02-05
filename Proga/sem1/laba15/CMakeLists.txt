cmake_minimum_required(VERSION 3.15)
project(laba15 C)

set(CMAKE_C_STANDARD 99)

add_executable(laba15 main.c settings.h settings.c arch.c arch.h files.c files.h)