cmake_minimum_required(VERSION 4.2)
project(3_LinearProgrammingEngine)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Used to Disable the build of GTest
if(DEFINED SKBUILD)
    set(LP_ENGINE_BUILD_TESTS_DEFAULT OFF)
else()
    set(LP_ENGINE_BUILD_TESTS_DEFAULT ON)
endif()

option(
    LP_ENGINE_BUILD_TESTS
    "Build LP Engine tests"
    ${LP_ENGINE_BUILD_TESTS_DEFAULT}
)

include(FetchContent)

FetchContent_Declare(
    pybind11
    URL https://github.com/pybind/pybind11/archive/refs/tags/v3.0.4.zip
)


FetchContent_MakeAvailable(pybind11)

if(LP_ENGINE_BUILD_TESTS)

    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )

    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    FetchContent_MakeAvailable(googletest)
endif()

add_library(
    SolverLibrary
    include/common/enums.h
    src/simplex/simplex_maincore.cpp
    include/simplex/simplex_maincore.h
    src/simplex/tableau.cpp
    include/simplex/tableau.h
    src/modeling/decision_variable.cpp
    include/modeling/decision_variable.h
    src/interface/lp_solver.cpp
    include/interface/lp_solver.h
    src/modeling/relation_expression.cpp
    include/modeling/relation_expression.h
    src/modeling/relation_exp_wrapper.cpp
    include/modeling/relation_exp_wrapper.h
    src/simplex/tableau_builder.cpp
    include/simplex/tableau_builder.h
)

target_include_directories(
    SolverLibrary
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_compile_features(
    SolverLibrary
    PUBLIC
    cxx_std_20
)

set_target_properties(
    SolverLibrary
    PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)


pybind11_add_module(
    lpengine
    src/interface/bindings.cpp)

target_link_libraries(
    lpengine
    PRIVATE
    SolverLibrary
)

install(
    TARGETS lpengine
    LIBRARY DESTINATION .
    RUNTIME DESTINATION .
)
install(
    FILES
    python/lpengine.pyi
    DESTINATION .
)

if(LP_ENGINE_BUILD_TESTS)
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
        tests/test_lp_frontend.cpp
        tests/system_test.cpp
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
endif()




