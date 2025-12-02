cmake_minimum_required(VERSION 4.0)
project(ac C)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES ac.c bool.c error.c)

add_executable(ac ${SOURCE_FILES})

