cmake_minimum_required(VERSION 3.0)
project(des C)

set(CMAKE_C_STANDARD 99)

add_executable(des main.c utility.c des.c constants.c)