cmake_minimum_required(VERSION 3.15)
project(DES C)

set(CMAKE_C_STANDARD 99)

add_executable(DES main.c utility.c des.c)