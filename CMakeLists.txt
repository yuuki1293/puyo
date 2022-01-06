cmake_minimum_required(VERSION 3.16)
project(mine_sweeper CXX)

set(CMAKE_CXX_FLAGS "-O2 -Wall")
include_directories(/usr/local/include)

add_executable(mine_sweeper main.cpp)

target_link_libraries(mine_sweeper eggx X11 m)