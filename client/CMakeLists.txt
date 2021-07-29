cmake_minimum_required(VERSION 3.16)

project(ClientModule)

find_package(cpr CONFIG REQUIRED)

set(HEADER_FILES Client.h connections.h)
set(SOURCE_FILES Client.cpp)

add_library(ClientModule STATIC
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

target_link_libraries(ClientModule PRIVATE cpr)