# CMakeLists.txt
# add library
cmake_minimum_required(VERSION 3.16)

project(GameModule)

set(HEADER_FILES Game.h Map.h Snake.h consts.h StartGame.h)
set(SOURCE_FILES Game.cpp Map.cpp Snake.cpp StartGame.cpp)

find_package(cpr CONFIG REQUIRED)

add_library(GameModule STATIC
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

target_include_directories(GameModule
    PUBLIC
        "../client"
)

target_link_libraries(GameModule
    PRIVATE
        ClientModule
        cpr
)