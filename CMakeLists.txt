cmake_minimum_required(VERSION 3.15)
project(sbus C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(test)
add_library(sbus src/sbus.c inc/sbus.h)