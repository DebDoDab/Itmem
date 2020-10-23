cmake_minimum_required(VERSION 3.17)
project(lab2_svyat)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab2_svyat main.cpp crc32.c tcp_connection.cpp tcp_connection.h dynamic_resource.cpp dynamic_resource.h hqsp.c hqsp.h)