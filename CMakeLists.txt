cmake_minimum_required(VERSION 3.0)

project(circ_buffer)

enable_testing()

set(SOURCE main.cpp)
set(STATIC_LIB circular_buffer.cpp)

add_subdirectory("googletest")
set(CMAKE_CXX_STANDARD 14)
add_library(circular_buffer STATIC ${STATIC_LIB})
add_executable(main ${SOURCE})
target_link_libraries(main circular_buffer gtest gmock)