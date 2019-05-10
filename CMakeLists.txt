cmake_minimum_required(VERSION 3.13)
project(test)

set(CMAKE_CXX_STANDARD 11)

add_executable(test hash.cpp)

set(CMAKE_CXX_FLAGS "-O0")
