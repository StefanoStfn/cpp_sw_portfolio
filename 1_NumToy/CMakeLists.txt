cmake_minimum_required(VERSION 4.2)
project(1_NumToy)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
    pybind11
    URL https://github.com/pybind/pybind11/archive/refs/tags/v3.0.4.zip
)


FetchContent_MakeAvailable(pybind11)

add_library(
    ntoy_lib
    src/ntoyarray.cpp
    include/ntoyarray.h
    src/numtoy_lib.cpp
    include/numtoy_lib.h
)

set_target_properties(ntoy_lib PROPERTIES POSITION_INDEPENDENT_CODE ON)

pybind11_add_module(
    numtoy
    src/bindings.cpp)

target_link_libraries(numtoy PRIVATE ntoy_lib)

install(TARGETS numtoy
    LIBRARY DESTINATION .
    RUNTIME DESTINATION .
)

enable_testing()

add_executable(
    test_lib
    tests/test_ntoyarray.cpp
    tests/test_sum.cpp
    tests/test_diff.cpp
    tests/test_mul.cpp
    tests/test_div.cpp
    tests/test_features.cpp
)

target_link_libraries(
    test_lib
    PRIVATE ntoy_lib
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_lib)
