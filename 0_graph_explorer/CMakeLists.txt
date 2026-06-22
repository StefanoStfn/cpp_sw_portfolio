cmake_minimum_required(VERSION 4.2.2)
project(graph_explorer)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(
    graph_explorer_lib
    src/graph.cpp
    src/node.cpp
    src/edge.cpp
    src/graph_flat.cpp
    include/graph_flat.h
)

target_include_directories(
    graph_explorer_lib
    PUBLIC include
)

add_executable(
    graph_explorer
    src/main.cpp
)

target_link_libraries(
    graph_explorer
    PRIVATE graph_explorer_lib
)

enable_testing()

add_executable(
    graph_explorer_tests
    tests/test_edge.cpp
    tests/test_node.cpp
    tests/test_graph.cpp
    tests/test_flat_graph.cpp
)

target_link_libraries(
    graph_explorer_tests
    PRIVATE graph_explorer_lib
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(graph_explorer_tests)


#if(CMAKE_BUILD_TYPE STREQUAL "Release")
#    target_compile_options(graph_explorer_lib PRIVATE
#        -O3
#        -march=native
#        #-flto
#        -funroll-loops
#    )
#    target_compile_options(graph_explorer PRIVATE
#        -O3
#        -march=native
#        #-flto
#        -funroll-loops
#    )
#    #target_link_options(graph_explorer PRIVATE -flto)
#endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(graph_explorer_lib PRIVATE
        /O2
        /GL
        /arch:AVX2
        /fp:fast
    )
    target_compile_options(graph_explorer PRIVATE
        /O2
        /GL
        /arch:AVX2
        /fp:fast
    )
    target_link_options(graph_explorer PRIVATE /LTCG)
endif()