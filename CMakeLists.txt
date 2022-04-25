cmake_minimum_required(VERSION 3.21)
project(smartptr)

set(CMAKE_CXX_STANDARD 14)

add_executable(smartptr main.cpp unique_ptr.h shared_ptr.h weak_ptr.h)
