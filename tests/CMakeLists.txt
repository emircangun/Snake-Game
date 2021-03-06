cmake_minimum_required(VERSION 3.16)

project(Tests)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(test ClientTest.cpp)

target_include_directories(test
    PUBLIC
        "../client"
        "../src"
)

target_link_libraries(test
    PRIVATE
        ClientModule
        GameModule
        gtest_main
)


include(GoogleTest)
gtest_discover_tests(test)