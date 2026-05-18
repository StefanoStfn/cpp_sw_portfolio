cmake_minimum_required(VERSION 4.2)
project(1_NumToy)

set(CMAKE_CXX_STANDARD 26)

add_executable(
    1_NumToy
    src/main.cpp
)

add_library(
    ntoy_lib
    src/ntoyarray.cpp
    include/ntoyarray.h
    src/numtoy_lib.cpp
    include/numtoy_lib.h
)

target_link_libraries(1_NumToy PRIVATE ntoy_lib)