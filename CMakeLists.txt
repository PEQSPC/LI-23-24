cmake_minimum_required(VERSION 3.26)
project(LIWORK C)

set(CMAKE_C_STANDARD 11)

add_executable(LIWORK main.c
        input_output.h
        input_output.c
        )
