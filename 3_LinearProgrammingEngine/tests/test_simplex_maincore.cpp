/**
* SimplexMainCore integration tests.
*
* These tests validate the full solver workflow starting from prebuilt
* simplex tableau. They exercise the state-machine execution path through
* pivoting, termination checks, reading, and final status assignment. The
* covered scenarios include feasible optimal solutions, unbounded problems,
* infeasible Big-M tableau, degenerate optima, alternative optimal solutions,
* cycling protection through iteration limits, and Bland-rule anti-cycling
* behavior. These tests verify engine-level behavior and result extraction,
* not low-level tableau arithmetic or LP preprocessing.
*/

#include <gtest/gtest.h>
#include "./fixtures/simplex_fixtures.h"
#include "../include/simplex_maincore.h"

TEST_F(FeasibleTableauTest, ExecutionTest)
{
    auto simplex_engine = LPEngine::SimplexMainCore(tableau);
    simplex_engine.startEngine();
    // Check Flags
    EXPECT_EQ(
        simplex_engine.getStatus(),
        LPEngine::SimplexMainCore::SolveStatus::Optimal
    );
    EXPECT_FALSE(simplex_engine.isDegenerateSolution());
    EXPECT_FALSE(simplex_engine.isAlternativeSolution());
    // Check internal expected variables
    EXPECT_NEAR(
        simplex_engine.getOptimaSolutionRHS(),
        260.0,
        1e-9
    );
    const auto values = simplex_engine.getVariableValues();
    EXPECT_NEAR(values.at("x"), 2.0, 1e-9);
    EXPECT_NEAR(values.at("y"), 5.0, 1e-9);
    EXPECT_NEAR(values.at("s1"), 1.0, 1e-9);
}

TEST_F(FractionalValueTableauTest, ExecutionTest)
{
    auto simplex_engine = LPEngine::SimplexMainCore(tableau);
    simplex_engine.startEngine();
    // Check Flags
    EXPECT_EQ(
        simplex_engine.getStatus(),
        LPEngine::SimplexMainCore::SolveStatus::Optimal
    );
    EXPECT_FALSE(simplex_engine.isDegenerateSolution());
    EXPECT_FALSE(simplex_engine.isAlternativeSolution());
    // Check internal expected variables
    EXPECT_NEAR(
        simplex_engine.getOptimaSolutionRHS(),
        8.4,
        1e-9
    );
    const auto values = simplex_engine.getVariableValues();
    EXPECT_NEAR(values.at("x"), 1.6, 1e-9);
    EXPECT_NEAR(values.at("y"), 1.8, 1e-9);
}

TEST_F(CycleFeasibleTableauTest, ExecutionTest)
{
    auto simplex_engine = LPEngine::SimplexMainCore(tableau);
    simplex_engine.startEngine();
    // Check Flags
    EXPECT_EQ(
        simplex_engine.getStatus(),
        LPEngine::SimplexMainCore::SolveStatus::Optimal
    );
    EXPECT_FALSE(simplex_engine.isDegenerateSolution());
    EXPECT_FALSE(simplex_engine.isAlternativeSolution());
    // Check internal expected variables
    EXPECT_NEAR(
        simplex_engine.getOptimaSolutionRHS(),
        1.0,
        1e-9
    );
    const auto values = simplex_engine.getVariableValues();
    EXPECT_NEAR(values.at("x1"), 1.0, 1e-9);
    EXPECT_NEAR(values.at("x2"), 0.0, 1e-9);
    EXPECT_NEAR(values.at("x3"), 1.0, 1e-9);
    EXPECT_NEAR(values.at("s1"), 2.0, 1e-9);
}

TEST_F(IterationLimitTableauTest, ExecutionTest)
{
    auto simplex_engine = LPEngine::SimplexMainCore(tableau);
    simplex_engine.startEngine();
    // Check Flags
    EXPECT_EQ(
        simplex_engine.getStatus(),
        LPEngine::SimplexMainCore::SolveStatus::IterationLimitReached
    );
    EXPECT_FALSE(simplex_engine.isDegenerateSolution());
    EXPECT_FALSE(simplex_engine.isAlternativeSolution());
}

TEST_F(UnboundedTableauTest, ExecutionTest)
{
    auto simplex_engine = LPEngine::SimplexMainCore(tableau);
    simplex_engine.startEngine();
    // Check Flags
    EXPECT_EQ(
        simplex_engine.getStatus(),
        LPEngine::SimplexMainCore::SolveStatus::Unbounded
    );
    EXPECT_FALSE(simplex_engine.isDegenerateSolution());
    EXPECT_FALSE(simplex_engine.isAlternativeSolution());
}

TEST_F(InfeasibleTableauTest, ExecutionTest)
{
    auto simplex_engine = LPEngine::SimplexMainCore(tableau);
    simplex_engine.startEngine();
    // Check Flags
    EXPECT_EQ(
        simplex_engine.getStatus(),
        LPEngine::SimplexMainCore::SolveStatus::Infeasible
    );
    EXPECT_FALSE(simplex_engine.isDegenerateSolution());
    EXPECT_FALSE(simplex_engine.isAlternativeSolution());
    // Check internal expected variables
    const auto values = simplex_engine.getVariableValues();
    EXPECT_NEAR(values.at("a1"), 5.0, 1e-9);
}

TEST_F(DegeneracyTableauTest, ExecutionTest)
{
    auto simplex_engine = LPEngine::SimplexMainCore(tableau);
    simplex_engine.startEngine();
    // Check Flags
    EXPECT_EQ(
        simplex_engine.getStatus(),
        LPEngine::SimplexMainCore::SolveStatus::Optimal
    );
    EXPECT_TRUE(simplex_engine.isDegenerateSolution());
    EXPECT_FALSE(simplex_engine.isAlternativeSolution());
    // Check internal expected variables
    EXPECT_NEAR(
        simplex_engine.getOptimaSolutionRHS(),
        12.0,
        1e-9
    );
    const auto values = simplex_engine.getVariableValues();
    EXPECT_NEAR(values.at("x1"), 2.0, 1e-9);
    EXPECT_NEAR(values.at("x2"), 0.0, 1e-9);
    EXPECT_NEAR(values.at("s1"), 0.0, 1e-9);
}

TEST_F(AlternativeOptSolTableauTest, ExecutionTest)
{
    auto simplex_engine = LPEngine::SimplexMainCore(tableau);
    simplex_engine.startEngine();
    // Check Flags
    EXPECT_EQ(
        simplex_engine.getStatus(),
        LPEngine::SimplexMainCore::SolveStatus::Optimal
    );
    EXPECT_FALSE(simplex_engine.isDegenerateSolution());
    EXPECT_TRUE(simplex_engine.isAlternativeSolution());
    // Check internal expected variables
    EXPECT_NEAR(
        simplex_engine.getOptimaSolutionRHS(),
        8.0,
        1e-9
    );
    const auto values = simplex_engine.getVariableValues();
    EXPECT_NEAR(values.at("x1"), 2.0, 1e-9);
    EXPECT_NEAR(values.at("x2"), 0.0, 1e-9);
}