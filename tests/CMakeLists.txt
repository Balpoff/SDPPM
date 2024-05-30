cmake_minimum_required(VERSION 3.0.0)

set(This auto-tests)

set(Sources
    tests.cpp
)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC
    gtest_main
    auto
)

add_test(
    NAME ${This}
    COMMAND ${This}
)