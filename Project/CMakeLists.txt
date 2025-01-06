cmake_minimum_required(VERSION 3.28)
project(Project C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(Project main.c
        src/function.c
        include/function.h
        include/datatype.h)
