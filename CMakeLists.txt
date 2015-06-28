cmake_minimum_required(VERSION 3.2)
project(TP3___Implementacion)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(TP3___Implementacion ${SOURCE_FILES} red.h TiposSimples.h)