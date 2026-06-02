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
    SolverLibrary
    src/simplex_maincore.cpp
    include/simplex_maincore.h
    src/tableau.cpp
    include/tableau.h
    src/decision_variable.cpp
    include/decision_variable.h
    src/lp_solver.cpp
    include/lp_solver.h
    src/relation_expression.cpp
    include/relation_expression.h
    src/relation_exp_wrapper.cpp
    include/relation_exp_wrapper.h
)

target_link_libraries(
    3_LinearProgrammingEngine
    PRIVATE SolverLibrary
)

enable_testing()

add_library(
    SimplexFixtureLib
    tests/fixtures/simplex_fixtures.h
    tests/fixtures/simplex_fixtures.cpp
)

target_link_libraries(
    SimplexFixtureLib
    PUBLIC
    SolverLibrary
    GTest::gtest
)

add_executable(
    GoogleTestExec
    tests/test_tableau.cpp
    tests/test_simplex_maincore.cpp
    tests/test_relation_expression_operators.cpp
)

target_link_libraries(
    GoogleTestExec
    PRIVATE
    GTest::gtest_main
    SolverLibrary
    SimplexFixtureLib
)

include(GoogleTest)
gtest_discover_tests(GoogleTestExec)

