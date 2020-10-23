cmake_minimum_required(VERSION 3.17)
project(lab2_svyat)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(lab2_svyat main.cpp crc32.c tcp_connection.cpp tcp_connection.h dynamic_resource.cpp dynamic_resource.h hqsp.c hqsp.h processes/system_info.cpp processes/system_info.h processes/ps.cpp processes/ps.h processes/observer.h processes/observer.cpp processes/logger_wrapper.cpp processes/logger_wrapper.h processes/send_signal.cpp processes/send_signal.h processes/create_process.cpp processes/create_process.h server.cpp)