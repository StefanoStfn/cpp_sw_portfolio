/**
* Tableau unit-test fixture for the Phase II simplex core.
*
* The fixture initializes a known feasible tableau with slack variables,
* a valid initial basis, and column-name metadata. The tests verify that
* the Tableau class correctly handles objective-row inspection, RHS access,
* variable-name lookup, pivot execution, basis updates, and termination
* detection after repeated Gauss-Jordan pivot steps. This test focuses only
* on low-level tableau mechanics, not on full LP preprocessing or model
* construction.
*/

#include <gtest/gtest.h>
#include "../include/tableau.h"

class TableauTest : public ::testing::Test
{
    protected:
        LPEngine::Tableau tableau = LPEngine::Tableau(
            LPEngine::SolverStrategy::MostNegative
        );
        // Objective function first row
        // constraint following rows
        void SetUp() override
        {
            const std::vector<double> buffer = {
                -30, -40, 0, 0, 0, 1, 0,
                2, 1, 1, 0, 0, 0, 10,
                1, 1, 0, 1, 0, 0, 7,
                1, 2, 0, 0, 1, 0, 12
            };
            int row_dim = 4;
            int col_dim = 7;
            tableau.overrideBuffer(
                row_dim, col_dim, buffer
            );
            std::vector<int> basic_variables = {2, 3, 4};
            tableau.overrideBasicVariables(
                basic_variables
            );
            const std::map<int, std::string> variable_names = {
                {0, "x"},
                {1, "y"},
                {2, "s1"},
                {3, "s2"},
                {4, "s3"},
                {5, "P"},
                {6, "RHS"}
            };
            tableau.overrideVariableNames(
                variable_names
            );
        }
};


TEST_F(TableauTest, objectiveFunctionTest)
{
    // Test whether obj function is not solved
    //  --> expect reset value
    EXPECT_EQ(
        tableau.objectiveFunctionTest(),
        -1
    );

}

TEST_F(TableauTest, getterMethods)
{
    // getBasicVariables
    EXPECT_EQ(
        tableau.getBasicVariables(),
        std::vector<int>({2, 3, 4})
    );
    // getRHS
    EXPECT_DOUBLE_EQ(
        tableau.getRHS(2),
        10.0
    );
    EXPECT_DOUBLE_EQ(
        tableau.getRHS(3),
        7.0
    );
    EXPECT_DOUBLE_EQ(
        tableau.getRHS(4),
        12.0
    );
    // getObjFunctionRHS
    EXPECT_DOUBLE_EQ(
        tableau.getObjFunctionRHS(),
        0.0
    );
    // getColIdx --> expect reset value
    EXPECT_EQ(
        tableau.getColIdx(),
        0
    );
    // getRowIdx --> expect reset value
    EXPECT_EQ(
        tableau.getRowIdx(),
        0
    );
    // getVarName
    EXPECT_EQ(
        tableau.getVarName(2),
        "s1"
    );
    EXPECT_EQ(
        tableau.getVarName(0),
        "x"
    );
    EXPECT_EQ(
        tableau.getVarName(6),
        "RHS"
    );
    // ColumnNumber
    EXPECT_EQ(
        tableau.getColNum(),
        7
    );
    // getArtificialVariables --> return vector of int
    EXPECT_EQ(
        tableau.getArtificialVariables(),
        std::vector<int>({})
    );
    // getObjectiveFuncCoefficient
    //-30, -40, 0, 0, 0
    EXPECT_DOUBLE_EQ(
        tableau.getObjectiveFuncCoefficient(0),
        -30.0
    );
    EXPECT_DOUBLE_EQ(
        tableau.getObjectiveFuncCoefficient(2),
        0.0
    );
}

TEST_F(TableauTest, getterMethodsThrowTest)
{
    // getRHS
    EXPECT_THROW(
        tableau.getRHS(0),
        std::invalid_argument
    );
    EXPECT_THROW(
        tableau.getRHS(1),
        std::invalid_argument
    );
    EXPECT_THROW(
        tableau.getRHS(13),
        std::invalid_argument
    );
    // getVarName
    EXPECT_THROW(
        tableau.getVarName(-1),
        std::out_of_range
    );
    EXPECT_THROW(
        tableau.getVarName(9),
        std::out_of_range
    );
    // getObjectiveFuncCoefficient
    EXPECT_THROW(
        tableau.getObjectiveFuncCoefficient(7),
        std::invalid_argument
        );
    EXPECT_THROW(
        tableau.getObjectiveFuncCoefficient(6),
        std::invalid_argument
    );
}

TEST_F(TableauTest, PivotingExecution)
{
    tableau.executePivotStep();
    // Basic Variables
    EXPECT_EQ(
        tableau.getBasicVariables(),
        std::vector<int>({2, 3, 1})
    );
    // getColIdx --> expect y entry
    EXPECT_EQ(
        tableau.getColIdx(),
        1
        );
    // getRowIdx --> expect r3
    EXPECT_EQ(
        tableau.getRowIdx(),
        3
    );
    EXPECT_EQ(
        tableau.objectiveFunctionTest(),
        -1
    );
    // getObjectiveFuncCoefficient
    EXPECT_DOUBLE_EQ(
        tableau.getObjectiveFuncCoefficient(0),
        -10.0
    );
    EXPECT_DOUBLE_EQ(
        tableau.getObjectiveFuncCoefficient(1),
        0.0
    );
    // getObjFunctionRHS
    EXPECT_DOUBLE_EQ(
        tableau.getObjFunctionRHS(),
        240.0
    );
}

TEST_F(TableauTest, PivotingExecutionTermination)
{
    // Expect Termination after 2 cycles
    tableau.executePivotStep();
    tableau.executePivotStep();
    // Basic Variables
    EXPECT_EQ(
        tableau.getBasicVariables(),
        std::vector<int>({2, 0, 1})
    );
    // getColIdx --> expect y entry
    EXPECT_EQ(
        tableau.getColIdx(),
        0
        );
    // getRowIdx --> expect r3
    EXPECT_EQ(
        tableau.getRowIdx(),
        2
    );
    EXPECT_EQ(
        tableau.objectiveFunctionTest(),
        0
        );
    // getObjectiveFuncCoefficient
    EXPECT_DOUBLE_EQ(
        tableau.getObjectiveFuncCoefficient(0),
        0.0
    );
    EXPECT_DOUBLE_EQ(
        tableau.getObjectiveFuncCoefficient(1),
        0.0
    );
    // getObjFunctionRHS
    EXPECT_DOUBLE_EQ(
        tableau.getObjFunctionRHS(),
        260.0
    );
}