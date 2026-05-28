cmake_minimum_required(VERSION 4.2)
project(3_LinearProgrammingEngine)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_executable(
    3_LinearProgrammingEngine
    src/main.cpp
)

add_library(
    SimplexLibrary
    src/simplex_maincore.cpp
    include/simplex_maincore.h
    src/tableau.cpp
    include/tableau.h
)

target_link_libraries(
    3_LinearProgrammingEngine
    PRIVATE SimplexLibrary
)

enable_testing()

add_executable(
    GoogleTestExec
    tests/test_wrapper.cpp
)

target_link_libraries(
    GoogleTestExec
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(GoogleTestExec)
