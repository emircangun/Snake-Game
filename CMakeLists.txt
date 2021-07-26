# CMakeLists.txt

cmake_minimum_required(VERSION 3.16)

set(This snake-game-client)

project(${This})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add subdirectory libraries
add_subdirectory(src)
add_subdirectory(client)

# add executable
add_executable(main main.cpp)

target_include_directories(main
    PUBLIC 
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
        "${CMAKE_CURRENT_SOURCE_DIR}/client"
)

target_link_libraries(main
    PRIVATE
        GameModule
        ClientModule
)