/**
* Frontend compile tests for LPSolver.
*
* These tests validate the translation from user-facing LP expressions
* into the internal canonical tableau representation. They inspect the
* compiled model only: column mapping, objective coefficients, row
* coefficients, slack/surplus/artificial variables, and initial basis.
*/

#include <gtest/gtest.h>
#include "common/enums.h"
#include "interface/lp_solver.h"

TEST(LPSolverCompileTest, CompilesClassicFeasibleProblem)
{
    auto solver = LPEngine::LPSolver();
    auto x = solver.addVariable("x");
    auto y = solver.addVariable("y");
    auto expr = 2*x + y <= 10;
    auto expr2 = x + y <= 7;
    auto expr3 = x + 2*y <= 12;
    auto obj_func = 30*x + 40*y;
    solver.addConstraint(expr);
    solver.addConstraint(expr2);
    solver.addConstraint(expr3);
    solver.addObjectiveFunction(
        obj_func,
        LPEngine::OptimizationType::Maximize
    );
    solver.compileSolver();
    // CHECK Column Map
    auto col_map = solver.getColumnNameMap();
    EXPECT_EQ(col_map.at("x"), 0);
    EXPECT_EQ(col_map.at("y"), 1);
    EXPECT_EQ(col_map.at("s0"), 2);
    EXPECT_EQ(col_map.at("s1"), 3);
    EXPECT_EQ(col_map.at("s2"), 4);
    // CHECK OBJ Coefficients
    auto obj = solver.getObjective();
    auto obj_coeffs = obj.getCoefficients();
    EXPECT_NEAR(obj_coeffs.at("x"), -30, EPS);
    EXPECT_NEAR(obj_coeffs.at("y"), -40, EPS);
    // CHECK ROW Coefficients
    auto c0 = solver.getRowConstraint(0).getCoefficients();
    auto c1 = solver.getRowConstraint(1).getCoefficients();
    auto c2 = solver.getRowConstraint(2).getCoefficients();
    EXPECT_NEAR(c0.at("x"), 2, EPS);
    EXPECT_NEAR(c0.at("y"), 1, EPS);
    EXPECT_NEAR(c0.at("s0"), 1, EPS);
    EXPECT_NEAR(c0.at("RHS"), 10, EPS);
    EXPECT_NEAR(c1.at("x"), 1, EPS);
    EXPECT_NEAR(c1.at("y"), 1, EPS);
    EXPECT_NEAR(c1.at("s1"), 1, EPS);
    EXPECT_NEAR(c1.at("RHS"), 7, EPS);
    EXPECT_NEAR(c2.at("x"), 1, EPS);
    EXPECT_NEAR(c2.at("y"), 2, EPS);
    EXPECT_NEAR(c2.at("s2"), 1, EPS);
    EXPECT_NEAR(c2.at("RHS"), 12, EPS);
}

TEST(LPSolverCompileTest, CompilesSmallFeasibleProblem)
{
    LPEngine::LPSolver solver;

    auto x = solver.addVariable("x");
    auto y = solver.addVariable("y");
    solver.addConstraint(x + y <= 4);
    solver.addConstraint(x <= 2);
    solver.addConstraint(y <= 3);
    solver.addObjectiveFunction(
        3*x + 2*y,
        LPEngine::OptimizationType::Maximize
    );
    solver.compileSolver();
    // CHECK Column Map
    auto col_map = solver.getColumnNameMap();
    EXPECT_EQ(col_map.at("x"), 0);
    EXPECT_EQ(col_map.at("y"), 1);
    EXPECT_EQ(col_map.at("s0"), 2);
    EXPECT_EQ(col_map.at("s1"), 3);
    EXPECT_EQ(col_map.at("s2"), 4);
    // CHECK Basic Variables
    auto basic_vars = solver.getBasicVariables();

    ASSERT_EQ(basic_vars.size(), 3);
    EXPECT_EQ(basic_vars.at(0), col_map.at("s0"));
    EXPECT_EQ(basic_vars.at(1), col_map.at("s1"));
    EXPECT_EQ(basic_vars.at(2), col_map.at("s2"));
    // CHECK OBJ Coefficients
    auto obj_coeffs = solver.getObjective().getCoefficients();
    EXPECT_NEAR(obj_coeffs.at("x"), -3, EPS);
    EXPECT_NEAR(obj_coeffs.at("y"), -2, EPS);
    // CHECK ROW Coefficients
    auto c0 = solver.getRowConstraint(0).getCoefficients();
    auto c1 = solver.getRowConstraint(1).getCoefficients();
    auto c2 = solver.getRowConstraint(2).getCoefficients();
    EXPECT_NEAR(c0.at("x"), 1, EPS);
    EXPECT_NEAR(c0.at("y"), 1, EPS);
    EXPECT_NEAR(c0.at("s0"), 1, EPS);
    EXPECT_NEAR(c0.at("RHS"), 4, EPS);
    EXPECT_NEAR(c1.at("x"), 1, EPS);
    EXPECT_NEAR(c1.at("y"), 0, EPS);
    EXPECT_NEAR(c1.at("s1"), 1, EPS);
    EXPECT_NEAR(c1.at("RHS"), 2, EPS);
    EXPECT_NEAR(c2.at("x"), 0, EPS);
    EXPECT_NEAR(c2.at("y"), 1, EPS);
    EXPECT_NEAR(c2.at("s2"), 1, EPS);
    EXPECT_NEAR(c2.at("RHS"), 3, EPS);
}

TEST(LPSolverCompileTest, CompilesFiveVariableFeasibleProblem)
{
    LPEngine::LPSolver solver;
    auto x1 = solver.addVariable("x1");
    auto x2 = solver.addVariable("x2");
    auto x3 = solver.addVariable("x3");
    auto x4 = solver.addVariable("x4");
    auto x5 = solver.addVariable("x5");
    solver.addConstraint(x1 + x2 + x3 <= 20);
    solver.addConstraint(2*x2 + x4 <= 15);
    solver.addConstraint(x3 + x4 + x5 <= 18);
    solver.addConstraint(x1 + 3*x5 <= 25);
    solver.addObjectiveFunction(
        5*x1 + 4*x2 + 3*x3 + 2*x4 + x5,
        LPEngine::OptimizationType::Maximize
    );
    solver.compileSolver();
    // CHECK Column Map
    auto col_map = solver.getColumnNameMap();
    EXPECT_EQ(col_map.at("x1"), 0);
    EXPECT_EQ(col_map.at("x2"), 1);
    EXPECT_EQ(col_map.at("x3"), 2);
    EXPECT_EQ(col_map.at("x4"), 3);
    EXPECT_EQ(col_map.at("x5"), 4);
    EXPECT_EQ(col_map.at("s0"), 5);
    EXPECT_EQ(col_map.at("s1"), 6);
    EXPECT_EQ(col_map.at("s2"), 7);
    EXPECT_EQ(col_map.at("s3"), 8);
    // CHECK Basic Variables
    auto basic_vars = solver.getBasicVariables();

    ASSERT_EQ(basic_vars.size(), 4);
    EXPECT_EQ(basic_vars.at(0), col_map.at("s0"));
    EXPECT_EQ(basic_vars.at(1), col_map.at("s1"));
    EXPECT_EQ(basic_vars.at(2), col_map.at("s2"));
    EXPECT_EQ(basic_vars.at(3), col_map.at("s3"));
    // CHECK OBJ Coefficients
    auto obj_coeffs = solver.getObjective().getCoefficients();
    EXPECT_NEAR(obj_coeffs.at("x1"), -5, EPS);
    EXPECT_NEAR(obj_coeffs.at("x2"), -4, EPS);
    EXPECT_NEAR(obj_coeffs.at("x3"), -3, EPS);
    EXPECT_NEAR(obj_coeffs.at("x4"), -2, EPS);
    EXPECT_NEAR(obj_coeffs.at("x5"), -1, EPS);
    // CHECK ROW Coefficients
    auto c0 = solver.getRowConstraint(0).getCoefficients();
    auto c1 = solver.getRowConstraint(1).getCoefficients();
    auto c2 = solver.getRowConstraint(2).getCoefficients();
    auto c3 = solver.getRowConstraint(3).getCoefficients();
    EXPECT_NEAR(c0.at("x1"), 1, EPS);
    EXPECT_NEAR(c0.at("x2"), 1, EPS);
    EXPECT_NEAR(c0.at("x3"), 1, EPS);
    EXPECT_NEAR(c0.at("s0"), 1, EPS);
    EXPECT_NEAR(c0.at("RHS"), 20, EPS);
    EXPECT_NEAR(c1.at("x2"), 2, EPS);
    EXPECT_NEAR(c1.at("x4"), 1, EPS);
    EXPECT_NEAR(c1.at("s1"), 1, EPS);
    EXPECT_NEAR(c1.at("RHS"), 15, EPS);
    EXPECT_NEAR(c2.at("x3"), 1, EPS);
    EXPECT_NEAR(c2.at("x4"), 1, EPS);
    EXPECT_NEAR(c2.at("x5"), 1, EPS);
    EXPECT_NEAR(c2.at("s2"), 1, EPS);
    EXPECT_NEAR(c2.at("RHS"), 18, EPS);
    EXPECT_NEAR(c3.at("x1"), 1, EPS);
    EXPECT_NEAR(c3.at("x5"), 3, EPS);
    EXPECT_NEAR(c3.at("s3"), 1, EPS);
    EXPECT_NEAR(c3.at("RHS"), 25, EPS);
}

TEST(LPSolverCompileTest, CompilesMinimizeBigMProblem)
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

    solver.compileSolver();

    constexpr double M = 1e6;

    auto col_map = solver.getColumnNameMap();

    EXPECT_EQ(col_map.at("x"), 0);
    EXPECT_EQ(col_map.at("y"), 1);
    EXPECT_EQ(col_map.at("s0"), 2);
    EXPECT_EQ(col_map.at("s1"), 3);
    EXPECT_EQ(col_map.at("s2"), 4);
    EXPECT_EQ(col_map.at("a0"), 5);

    auto obj_coeffs = solver.getObjective().getCoefficients();

    EXPECT_NEAR(obj_coeffs.at("x"), 3 - M, EPS);
    EXPECT_NEAR(obj_coeffs.at("y"), 2 - M, EPS);
    EXPECT_NEAR(obj_coeffs.at("s0"), M, EPS);
    EXPECT_NEAR(obj_coeffs.at("a0"), 0, EPS);
    EXPECT_NEAR(obj_coeffs.at("RHS"), -10 * M, EPS);

    auto c0 = solver.getRowConstraint(0).getCoefficients();
    auto c1 = solver.getRowConstraint(1).getCoefficients();
    auto c2 = solver.getRowConstraint(2).getCoefficients();

    EXPECT_NEAR(c0.at("x"), 1, EPS);
    EXPECT_NEAR(c0.at("y"), 1, EPS);
    EXPECT_NEAR(c0.at("s0"), -1, EPS);
    EXPECT_NEAR(c0.at("a0"), 1, EPS);
    EXPECT_NEAR(c0.at("RHS"), 10, EPS);

    EXPECT_NEAR(c1.at("x"), 1, EPS);
    EXPECT_NEAR(c1.at("s1"), 1, EPS);
    EXPECT_NEAR(c1.at("RHS"), 8, EPS);

    EXPECT_NEAR(c2.at("y"), 1, EPS);
    EXPECT_NEAR(c2.at("s2"), 1, EPS);
    EXPECT_NEAR(c2.at("RHS"), 8, EPS);

    auto basic_vars = solver.getBasicVariables();

    ASSERT_EQ(basic_vars.size(), 3);
    EXPECT_EQ(basic_vars.at(0), col_map.at("a0"));
    EXPECT_EQ(basic_vars.at(1), col_map.at("s1"));
    EXPECT_EQ(basic_vars.at(2), col_map.at("s2"));
}

TEST(LPSolverCompileTest, CompilesAlternativeSolutionBigMProblem)
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

    solver.compileSolver();

    constexpr double M = 1e6;

    auto col_map = solver.getColumnNameMap();

    EXPECT_EQ(col_map.at("x1"), 0);
    EXPECT_EQ(col_map.at("x2"), 1);
    EXPECT_EQ(col_map.at("x3"), 2);
    EXPECT_EQ(col_map.at("x4"), 3);
    EXPECT_EQ(col_map.at("x5"), 4);
    EXPECT_EQ(col_map.at("s0"), 5);
    EXPECT_EQ(col_map.at("s1"), 6);
    EXPECT_EQ(col_map.at("s2"), 7);
    EXPECT_EQ(col_map.at("s3"), 8);
    EXPECT_EQ(col_map.at("s4"), 9);
    EXPECT_EQ(col_map.at("s5"), 10);
    EXPECT_EQ(col_map.at("a0"), 11);
    EXPECT_EQ(col_map.at("a1"), 12);

    auto obj_coeffs = solver.getObjective().getCoefficients();

    EXPECT_NEAR(obj_coeffs.at("x1"), -3 - M, EPS);
    EXPECT_NEAR(obj_coeffs.at("x2"), -3 - M, EPS);
    EXPECT_NEAR(obj_coeffs.at("x3"), -3 - M, EPS);
    EXPECT_NEAR(obj_coeffs.at("x4"), -M, EPS);
    EXPECT_NEAR(obj_coeffs.at("x5"), -M, EPS);
    EXPECT_NEAR(obj_coeffs.at("s0"), M, EPS);
    EXPECT_NEAR(obj_coeffs.at("a0"), 0, EPS);
    EXPECT_NEAR(obj_coeffs.at("a1"), 0, EPS);
    EXPECT_NEAR(obj_coeffs.at("RHS"), -14 * M, EPS);

    auto c0 = solver.getRowConstraint(0).getCoefficients();
    auto c1 = solver.getRowConstraint(1).getCoefficients();

    EXPECT_NEAR(c0.at("x1"), 1, EPS);
    EXPECT_NEAR(c0.at("x2"), 1, EPS);
    EXPECT_NEAR(c0.at("x3"), 1, EPS);
    EXPECT_NEAR(c0.at("a0"), 1, EPS);
    EXPECT_NEAR(c0.at("RHS"), 10, EPS);

    EXPECT_NEAR(c1.at("x4"), 1, EPS);
    EXPECT_NEAR(c1.at("x5"), 1, EPS);
    EXPECT_NEAR(c1.at("s0"), -1, EPS);
    EXPECT_NEAR(c1.at("a1"), 1, EPS);
    EXPECT_NEAR(c1.at("RHS"), 4, EPS);

    auto basic_vars = solver.getBasicVariables();

    ASSERT_EQ(basic_vars.size(), 7);
    EXPECT_EQ(basic_vars.at(0), col_map.at("a0"));
    EXPECT_EQ(basic_vars.at(1), col_map.at("a1"));
    EXPECT_EQ(basic_vars.at(2), col_map.at("s1"));
    EXPECT_EQ(basic_vars.at(3), col_map.at("s2"));
    EXPECT_EQ(basic_vars.at(4), col_map.at("s3"));
    EXPECT_EQ(basic_vars.at(5), col_map.at("s4"));
    EXPECT_EQ(basic_vars.at(6), col_map.at("s5"));
}

TEST(LPSolverCompileTest, CompilesMinimizeAlternativeBigMProblem)
{
    auto solver = LPEngine::LPSolver();

    auto x = solver.addVariable("x");
    auto y = solver.addVariable("y");
    auto z = solver.addVariable("z");

    solver.addConstraint(x + y + z >= 6);
    solver.addConstraint(x <= 4);
    solver.addConstraint(y <= 4);
    solver.addConstraint(z <= 4);

    solver.addObjectiveFunction(
        2*x + y + z,
        LPEngine::OptimizationType::Minimize
    );

    solver.compileSolver();

    constexpr double M = 1e6;

    auto col_map = solver.getColumnNameMap();

    EXPECT_EQ(col_map.at("x"), 0);
    EXPECT_EQ(col_map.at("y"), 1);
    EXPECT_EQ(col_map.at("z"), 2);
    EXPECT_EQ(col_map.at("s0"), 3);
    EXPECT_EQ(col_map.at("s1"), 4);
    EXPECT_EQ(col_map.at("s2"), 5);
    EXPECT_EQ(col_map.at("s3"), 6);
    EXPECT_EQ(col_map.at("a0"), 7);

    auto obj_coeffs = solver.getObjective().getCoefficients();

    EXPECT_NEAR(obj_coeffs.at("x"), 2 - M, EPS);
    EXPECT_NEAR(obj_coeffs.at("y"), 1 - M, EPS);
    EXPECT_NEAR(obj_coeffs.at("z"), 1 - M, EPS);
    EXPECT_NEAR(obj_coeffs.at("s0"), M, EPS);
    EXPECT_NEAR(obj_coeffs.at("a0"), 0, EPS);
    EXPECT_NEAR(obj_coeffs.at("RHS"), -6 * M, EPS);

    auto c0 = solver.getRowConstraint(0).getCoefficients();
    auto c1 = solver.getRowConstraint(1).getCoefficients();
    auto c2 = solver.getRowConstraint(2).getCoefficients();
    auto c3 = solver.getRowConstraint(3).getCoefficients();

    EXPECT_NEAR(c0.at("x"), 1, EPS);
    EXPECT_NEAR(c0.at("y"), 1, EPS);
    EXPECT_NEAR(c0.at("z"), 1, EPS);
    EXPECT_NEAR(c0.at("s0"), -1, EPS);
    EXPECT_NEAR(c0.at("a0"), 1, EPS);
    EXPECT_NEAR(c0.at("RHS"), 6, EPS);

    EXPECT_NEAR(c1.at("x"), 1, EPS);
    EXPECT_NEAR(c1.at("s1"), 1, EPS);
    EXPECT_NEAR(c1.at("RHS"), 4, EPS);

    EXPECT_NEAR(c2.at("y"), 1, EPS);
    EXPECT_NEAR(c2.at("s2"), 1, EPS);
    EXPECT_NEAR(c2.at("RHS"), 4, EPS);

    EXPECT_NEAR(c3.at("z"), 1, EPS);
    EXPECT_NEAR(c3.at("s3"), 1, EPS);
    EXPECT_NEAR(c3.at("RHS"), 4, EPS);

    auto basic_vars = solver.getBasicVariables();

    ASSERT_EQ(basic_vars.size(), 4);
    EXPECT_EQ(basic_vars.at(0), col_map.at("a0"));
    EXPECT_EQ(basic_vars.at(1), col_map.at("s1"));
    EXPECT_EQ(basic_vars.at(2), col_map.at("s2"));
    EXPECT_EQ(basic_vars.at(3), col_map.at("s3"));
}
