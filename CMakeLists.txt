cmake_minimum_required(VERSION 3.20)
project(traffic_engineering)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(traffic_engineering include/switch.h src/switch.cpp include/tunnel.h src/tunnel.cpp include/network.h src/network.cpp include/adjustment.h src/adjustment.cpp)
