cmake_minimum_required(VERSION 3.16)

project(Tests)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(test ClientTest.cpp)

target_include_directories(test
    PUBLIC
        "../client"
)

target_link_libraries(test
    PRIVATE
        ClientModule
)