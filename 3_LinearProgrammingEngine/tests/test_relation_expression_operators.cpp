/**
* RelationExpression operator and string formatting tests.
*
* These tests validate the frontend algebra layer used by the LP modeling API.
* They verify scalar-variable products, expression addition/subtraction,
* repeated-variable coefficient accumulation, scalar multiplication of full
* expressions, relation/RHS attachment, and human-readable string formatting.
* The tests ensure C++ operator chains produce the expected RelationExpression
* before the expression is committed into the solver system.
*/

#include <gtest/gtest.h>
#include "../include/relation_exp_wrapper.h"

class RelationExpressionTest : public ::testing::Test
{
protected:
    LPEngine::DecisionVariable x1{"x1", 0};
    LPEngine::DecisionVariable x2{"x2", 1};
    LPEngine::DecisionVariable x3{"x3", 2};
};

TEST_F(RelationExpressionTest, ScalarTimesVariableCreatesExpression)
{
    auto expr = 3.0 * x1;
    const auto coeffs = expr.getCoefficients();

    EXPECT_DOUBLE_EQ(coeffs.at("x1"), 3.0);
}

TEST_F(RelationExpressionTest, VariableTimesScalarCreatesExpression)
{
    auto expr = x1 * 3.0;
    const auto coeffs = expr.getCoefficients();

    EXPECT_DOUBLE_EQ(coeffs.at("x1"), 3.0);
}

TEST_F(RelationExpressionTest, VariablePlusVariableCreatesExpression)
{
    auto expr = x1 + x2;
    const auto coeffs = expr.getCoefficients();

    EXPECT_DOUBLE_EQ(coeffs.at("x1"), 1.0);
    EXPECT_DOUBLE_EQ(coeffs.at("x2"), 1.0);
}

TEST_F(RelationExpressionTest, VariableMinusVariableCreatesExpression)
{
    auto expr = x1 - x2;
    const auto coeffs = expr.getCoefficients();

    EXPECT_DOUBLE_EQ(coeffs.at("x1"), 1.0);
    EXPECT_DOUBLE_EQ(coeffs.at("x2"), -1.0);
}

TEST_F(RelationExpressionTest, ExpressionAddsVariable)
{
    auto expr = 3.0 * x1 + x2;
    const auto coeffs = expr.getCoefficients();

    EXPECT_DOUBLE_EQ(coeffs.at("x1"), 3.0);
    EXPECT_DOUBLE_EQ(coeffs.at("x2"), 1.0);
}

TEST_F(RelationExpressionTest, VariableAddsExpression)
{
    auto expr = x1 + 4.0 * x2;
    const auto coeffs = expr.getCoefficients();

    EXPECT_DOUBLE_EQ(coeffs.at("x1"), 1.0);
    EXPECT_DOUBLE_EQ(coeffs.at("x2"), 4.0);
}

TEST_F(RelationExpressionTest, ExpressionSubtractsVariable)
{
    auto expr = 3.0 * x1 - x2;
    const auto coeffs = expr.getCoefficients();

    EXPECT_DOUBLE_EQ(coeffs.at("x1"), 3.0);
    EXPECT_DOUBLE_EQ(coeffs.at("x2"), -1.0);
}

TEST_F(RelationExpressionTest, VariableSubtractsExpression)
{
    auto expr = x1 - (2.0 * x2 + x3);
    const auto coeffs = expr.getCoefficients();

    EXPECT_DOUBLE_EQ(coeffs.at("x1"), 1.0);
    EXPECT_DOUBLE_EQ(coeffs.at("x2"), -2.0);
    EXPECT_DOUBLE_EQ(coeffs.at("x3"), -1.0);
}

TEST_F(RelationExpressionTest, ExpressionPlusExpressionMergesCoefficients)
{
    auto expr = (3.0 * x1 + 2.0 * x2) + (5.0 * x1 + 4.0 * x3);
    const auto coeffs = expr.getCoefficients();

    EXPECT_DOUBLE_EQ(coeffs.at("x1"), 8.0);
    EXPECT_DOUBLE_EQ(coeffs.at("x2"), 2.0);
    EXPECT_DOUBLE_EQ(coeffs.at("x3"), 4.0);
}

TEST_F(RelationExpressionTest, ExpressionMinusExpressionMergesCoefficients)
{
    auto expr = (3.0 * x1 + 2.0 * x2) - (5.0 * x1 + 4.0 * x3);
    const auto coeffs = expr.getCoefficients();

    EXPECT_DOUBLE_EQ(coeffs.at("x1"), -2.0);
    EXPECT_DOUBLE_EQ(coeffs.at("x2"), 2.0);
    EXPECT_DOUBLE_EQ(coeffs.at("x3"), -4.0);
}

TEST_F(RelationExpressionTest, RepeatedVariablesAreAccumulated)
{
    auto expr = x1 * 3.0 - 4.0 * x2 + 8.0 * x3 + 2.0 * x1;
    const auto coeffs = expr.getCoefficients();

    EXPECT_DOUBLE_EQ(coeffs.at("x1"), 5.0);
    EXPECT_DOUBLE_EQ(coeffs.at("x2"), -4.0);
    EXPECT_DOUBLE_EQ(coeffs.at("x3"), 8.0);
}

TEST_F(RelationExpressionTest, ScalarMultiplicationOfExpressionWorks)
{
    auto expr = 5.0 * (x1 * 3.0 - 4.0 * x2) + 8.0 * x3 - 2.0 * x1;
    const auto coeffs = expr.getCoefficients();

    EXPECT_DOUBLE_EQ(coeffs.at("x1"), 13.0);
    EXPECT_DOUBLE_EQ(coeffs.at("x2"), -20.0);
    EXPECT_DOUBLE_EQ(coeffs.at("x3"), 8.0);
}

TEST_F(RelationExpressionTest, GreaterEqualAddsRHSAndSense)
{
    auto expr = x1 * 3.0 - 4.0 * x2 >= 3.0;
    const auto coeffs = expr.getCoefficients();

    EXPECT_DOUBLE_EQ(coeffs.at("x1"), 3.0);
    EXPECT_DOUBLE_EQ(coeffs.at("x2"), -4.0);
    EXPECT_DOUBLE_EQ(coeffs.at(RHS_KEY), 3.0);
    EXPECT_EQ(expr.getConstraintSense(), LPEngine::ConstraintSense::GreaterEqual);
}

TEST_F(RelationExpressionTest, LessEqualAddsRHSAndSense)
{
    auto expr = x1 * 3.0 + 2.0 * x2 <= 10.0;
    const auto coeffs = expr.getCoefficients();

    EXPECT_DOUBLE_EQ(coeffs.at("x1"), 3.0);
    EXPECT_DOUBLE_EQ(coeffs.at("x2"), 2.0);
    EXPECT_DOUBLE_EQ(coeffs.at(RHS_KEY), 10.0);
    EXPECT_EQ(expr.getConstraintSense(), LPEngine::ConstraintSense::LessEqual);
}

TEST_F(RelationExpressionTest, EqualAddsRHSAndSense)
{
    auto expr = x1 + x2 == 5.0;
    const auto coeffs = expr.getCoefficients();

    EXPECT_DOUBLE_EQ(coeffs.at("x1"), 1.0);
    EXPECT_DOUBLE_EQ(coeffs.at("x2"), 1.0);
    EXPECT_DOUBLE_EQ(coeffs.at(RHS_KEY), 5.0);
    EXPECT_EQ(expr.getConstraintSense(), LPEngine::ConstraintSense::Equal);
}

TEST_F(RelationExpressionTest, ToStringFormatsPositiveAndNegativeTerms)
{
    auto expr = x1 * 3.0 - 4.0 * x2 >= 3.0;

    EXPECT_EQ(
        expr.toString(),
        "3*x1 - 4*x2 >= 3"
    );
}

TEST_F(RelationExpressionTest, ToStringAccumulatesRepeatedVariables)
{
    auto expr = x1 * 3.0 - 4.0 * x2 + 8.0 * x3 + 2.0 * x1 >= 3.0;

    EXPECT_EQ(
        expr.toString(),
        "5*x1 - 4*x2 + 8*x3 >= 3"
    );
}

TEST_F(RelationExpressionTest, ToStringFormatsScalarMultipliedExpression)
{
    auto expr = 5.0 * (x1 * 3.0 - 4.0 * x2) + 8.0 * x3 - 2.0 * x1 >= 3.0;

    EXPECT_EQ(
        expr.toString(),
        "13*x1 - 20*x2 + 8*x3 >= 3"
    );
}

TEST_F(RelationExpressionTest, ToStringFormatsLessEqualRelation)
{
    auto expr = x1 * 3.0 + 2.0 * x2 <= 10.0;

    EXPECT_EQ(
        expr.toString(),
        "3*x1 + 2*x2 <= 10"
    );
}

TEST_F(RelationExpressionTest, ToStringFormatsEqualRelation)
{
    auto expr = x1 + x2 == 5.0;

    EXPECT_EQ(
        expr.toString(),
        "1*x1 + 1*x2 == 5"
    );
}