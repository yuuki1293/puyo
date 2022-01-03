cmake_minimum_required(VERSION 3.16)
project(puyo CXX)

set(CMAKE_CXX_FLAGS "-O2 -Wall")
include_directories(/usr/local/include)

add_executable(puyo main.cpp)

target_link_libraries(puyo eggx X11 m)