/**
* Tableau unit-test fixtures for the Phase II simplex core.
*
* The tests initialize known simplex tableau with valid basis metadata,
* column-name mappings, and solver-strategy configuration. They verify that
* the Tableau class correctly handles objective-row inspection, RHS access,
* variable-name lookup, pivot execution, basis updates, termination detection,
* and strategy-dependent entering-variable selection. The fixtures focus only
* on low-level tableau mechanics, including Gauss-Jordan pivoting and Bland
* versus most-negative pivot behavior, not on LP preprocessing or model
* construction.
*/
#include "common/enums.h"
#include "fixtures/simplex_fixtures.h"

TEST_F(FeasibleTableauTest, objectiveFunctionTest)
{
    // Test whether obj function is not solved
    //  --> expect reset value
    EXPECT_EQ(
        tableau.objectiveFunctionTest(),
        -1
    );
}

TEST_F(FeasibleTableauTest, getterMethods)
{
    // getBasicVariables
    EXPECT_EQ(
        tableau.getBasicVariables(),
        std::vector<int>({2, 3, 4})
    );
    // getRHS
    EXPECT_NEAR(
        tableau.getRHS(2),
        10.0,
        EPS
    );
    EXPECT_NEAR(
        tableau.getRHS(3),
        7.0,
        EPS
    );
    EXPECT_NEAR(
        tableau.getRHS(4),
        12.0,
        EPS
    );
    // getObjFunctionRHS
    EXPECT_NEAR(
        tableau.getObjFunctionRHS(),
        0.0,
        EPS
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
    EXPECT_NEAR(
        tableau.getObjectiveFuncCoefficient(0),
        -30.0,
        EPS
    );
    EXPECT_NEAR(
        tableau.getObjectiveFuncCoefficient(2),
        0.0,
        EPS
    );
}

TEST_F(FeasibleTableauTest, getterMethodsThrowTest)
{
    // getRHS
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

TEST_F(FeasibleTableauTest, PivotingExecution)
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
    EXPECT_NEAR(
        tableau.getObjectiveFuncCoefficient(0),
        -10.0,
        EPS
    );
    EXPECT_NEAR(
        tableau.getObjectiveFuncCoefficient(1),
        0.0,
        EPS
    );
    // getObjFunctionRHS
    EXPECT_NEAR(
        tableau.getObjFunctionRHS(),
        240.0,
        EPS
    );
}

TEST_F(FeasibleTableauTest, PivotingExecutionTermination)
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
    EXPECT_NEAR(
        tableau.getObjectiveFuncCoefficient(0),
        0.0,
        EPS
    );
    EXPECT_NEAR(
        tableau.getObjectiveFuncCoefficient(1),
        0.0,
        EPS
    );
    // getObjFunctionRHS
    EXPECT_NEAR(
        tableau.getObjFunctionRHS(),
        260.0,
        EPS
    );
}

TEST_F(CycleFeasibleTableauTest, CheckColumnPicking)
{
    tableau.executePivotStep();
    // getColIdx --> for bland rule the first negative coefficient
    // Normally the second should've been picked
    EXPECT_EQ(
        tableau.getColIdx(),
        0
    );

}