/**
* End-to-end system tests for LPSolver.
*
* These tests validate the full LP execution path from frontend modeling
* expressions to final solver results. Unlike compile tests, they call run()
* and verify solver status, optimal objective values, variable assignments,
* infeasibility detection, unboundedness detection, Big-M behavior,
* minimization reporting, degeneracy flags, and alternative-solution flags.
*/

#include <gtest/gtest.h>
#include "common/enums.h"
#include "interface/lp_solver.h"

TEST(LPSolverSystemTest, SolvesClassicFeasibleProblem)
{
    auto solver = LPEngine::LPSolver();
    auto x = solver.addVariable("x");
    auto y = solver.addVariable("y");
    solver.addConstraint(2*x + y <= 10);
    solver.addConstraint(x + y <= 7);
    solver.addConstraint(x + 2*y <= 12);
    solver.addObjectiveFunction(
        30*x + 40*y,
        LPEngine::OptimizationType::Maximize
    );
    solver.run();

    EXPECT_EQ(solver.getStatus(), LPEngine::SolveStatus::Optimal);
    EXPECT_NEAR(solver.getOptimaSolutionRHS(), 260, EPS);
    auto values = solver.getVariableValues();
    EXPECT_NEAR(values.at("x"), 2, EPS);
    EXPECT_NEAR(values.at("y"), 5, EPS);
}

TEST(LPSolverSystemTest, SolvesMinimizeBigMProblem)
{
    auto solver = LPEngine::LPSolver();
    auto x = solver.addVariable("x");
    auto y = solver.addVariable("y");
    solver.addConstraint(x + y >= 10);
    solver.addConstraint(x <= 8);
    solver.addConstraint(y <= 8);
    solver.addObjectiveFunction(
        3*x + 2*y,
        LPEngine::OptimizationType::Minimize
    );
    solver.run();
    
    EXPECT_EQ(solver.getStatus(), LPEngine::SolveStatus::Optimal);
    EXPECT_NEAR(solver.getOptimaSolutionRHS(), 22, EPS);
    auto values = solver.getVariableValues();
    EXPECT_NEAR(values.at("x"), 2, EPS);
    EXPECT_NEAR(values.at("y"), 8, EPS);
    EXPECT_NEAR(values.at("a0"), 0, EPS);
}

TEST(LPSolverSystemTest, SolvesFiveVariableMixedBigMProblem)
{
    auto solver = LPEngine::LPSolver();
    auto x1 = solver.addVariable("x1");
    auto x2 = solver.addVariable("x2");
    auto x3 = solver.addVariable("x3");
    auto x4 = solver.addVariable("x4");
    auto x5 = solver.addVariable("x5");
    solver.addConstraint(x1 + x2 + x3 == 10);
    solver.addConstraint(x4 + x5 >= 4);
    solver.addConstraint(x1 + x4 <= 12);
    solver.addConstraint(x2 + x5 <= 12);
    solver.addConstraint(x3 + x4 + x5 <= 14);
    solver.addConstraint(x4 <= 6);
    solver.addConstraint(x5 <= 6);
    solver.addObjectiveFunction(
        3*x1 + 3*x2 + 3*x3,
        LPEngine::OptimizationType::Maximize
    );
    solver.run();

    EXPECT_EQ(solver.getStatus(), LPEngine::SolveStatus::Optimal);
    EXPECT_NEAR(solver.getOptimaSolutionRHS(), 30.0, EPS);
    auto values = solver.getVariableValues();
    EXPECT_TRUE(solver.isAlternativeSolution());
}

TEST(LPSolverSystemTest, DetectsInfeasibleProblem)
{
    auto solver = LPEngine::LPSolver();
    auto x = solver.addVariable("x");
    auto y = solver.addVariable("y");
    solver.addConstraint(x + y >= 10);
    solver.addConstraint(x + y <= 5);
    solver.addObjectiveFunction(
        x + y,
        LPEngine::OptimizationType::Maximize
    );
    solver.run();

    EXPECT_EQ(solver.getStatus(), LPEngine::SolveStatus::Infeasible);
    auto values = solver.getVariableValues();
    EXPECT_NEAR(values.at("a0"), 5.0, EPS);
}

TEST(LPSolverSystemTest, DetectsUnboundedProblem)
{
    auto solver = LPEngine::LPSolver();
    auto x = solver.addVariable("x");
    auto y = solver.addVariable("y");
    solver.addConstraint(x - y <= 1);
    solver.addObjectiveFunction(
        x + y,
        LPEngine::OptimizationType::Maximize
    );
    solver.run();

    EXPECT_EQ(solver.getStatus(), LPEngine::SolveStatus::Unbounded);
}

TEST(LPSolverSystemTest, SolvesDegenerateMinimizeProblem)
{
    auto solver = LPEngine::LPSolver();
    auto x = solver.addVariable("x");
    auto y = solver.addVariable("y");
    solver.addConstraint(x + y >= 2);
    solver.addConstraint(x >= 1);
    solver.addConstraint(y >= 1);
    solver.addConstraint(x <= 2);
    solver.addConstraint(y <= 2);
    solver.addObjectiveFunction(
        x + y,
        LPEngine::OptimizationType::Minimize
    );
    solver.run();

    EXPECT_EQ(solver.getStatus(), LPEngine::SolveStatus::Optimal);
    EXPECT_NEAR(solver.getOptimaSolutionRHS(), 2.0, EPS);
    auto values = solver.getVariableValues();
    EXPECT_NEAR(values.at("x"), 1.0, EPS);
    EXPECT_NEAR(values.at("y"), 1.0, EPS);
    EXPECT_TRUE(solver.isDegenerateSolution());
}