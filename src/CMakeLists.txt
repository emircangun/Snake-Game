# CMakeLists.txt
# add library
cmake_minimum_required(VERSION 3.16)

project(GameModule)

set(HEADER_FILES Game.h Map.h Snake.h)
set(SOURCE_FILES Game.cpp Map.cpp Snake.cpp)

add_library(GameModule STATIC
    ${SOURCE_FILES}
    ${HEADER_FILES}
)