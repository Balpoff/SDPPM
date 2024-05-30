cmake_minimum_required(VERSION 3.0.0)

set(This auto)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

set(Headers
    funcs.h
)
set(Sources
    funcs.cpp
)

add_library(${This} STATIC ${Sources} ${HEaders})
add_subdirectory(tests)
