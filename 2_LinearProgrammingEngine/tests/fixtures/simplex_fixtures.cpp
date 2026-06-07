/**
* Fixture implementations for SimplexMainCore integration tests.
*
* Each SetUp method builds a complete mock simplex tableau for a specific
* solver scenario: feasible optimality, cycling/anti-cycling behavior,
* unboundedness, infeasibility, degeneracy, or alternative optimal solutions.
* The setup includes the flattened tableau buffer, dimensions, initial basis,
* variable-name mapping, and artificial-variable metadata when required.
* they are used to test the solver workflow starting from a ready-to-solve
* simplex tableau.
*/

#include "simplex_fixtures.h"

void FeasibleTableauTest::SetUp()
{
    // Objective function first row
    // constraint following rows
    const std::vector<double> buffer = {
        -30, -40, 0, 0, 0, 1, 0,
        2, 1, 1, 0, 0, 0, 10,
        1, 1, 0, 1, 0, 0, 7,
        1, 2, 0, 0, 1, 0, 12
    };
    int row_dim = 4;
    int col_dim = 7;
    tableau.setBuffer(
        row_dim, col_dim, buffer
    );
    std::vector<int> basic_variables = {2, 3, 4};
    tableau.setBasicVariables(
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
    tableau.setVariableNames(
        variable_names
    );
}

void FractionalValueTableauTest::SetUp()
{
    // Objective function first row
    // constraint following rows
    const std::vector<double> buffer = {
        -3, -2, 0, 0, 1, 0,
         2,  1, 1, 0, 0, 5,
         1,  3, 0, 1, 0, 7
    };
    int row_dim = 3;
    int col_dim = 6;
    tableau.setBuffer(
        row_dim, col_dim, buffer
    );
    std::vector<int> basic_variables = {2, 3};
    tableau.setBasicVariables(
        basic_variables
    );
    const std::map<int, std::string> variable_names = {
        {0, "x"},
        {1, "y"},
        {2, "s1"},
        {3, "s2"},
        {4, "P"},
        {5, "RHS"}
    };
    tableau.setVariableNames(
        variable_names
    );
}

void CycleFeasibleTableauTest::SetUp()
{
    // Objective function first row
    // constraint following rows
    const std::vector<double> buffer = {
        -10, 57, 9, 24, 0, 0, 0, 1, 0,
        0.5, -5.5, -2.5, 9, 1, 0, 0, 0, 0,
        0.5, -1.5, -0.5, 1, 0, 1, 0, 0, 0,
        1, 0, 0, 0, 0, 0, 1, 0, 1
    };
    int row_dim = 4;
    int col_dim = 9;
    tableau.setBuffer(
        row_dim, col_dim, buffer
    );
    std::vector<int> basic_variables = {4, 5, 6};
    tableau.setBasicVariables(
        basic_variables
    );
    const std::map<int, std::string> variable_names = {
        {0, "x1"},
        {1, "x2"},
        {2, "x3"},
        {3, "x4"},
        {4, "s1"},
        {5, "s2"},
        {6, "s3"},
        {7, "P"},
        {8, "RHS"}
    };
    tableau.setVariableNames(
        variable_names
    );
}

void IterationLimitTableauTest::SetUp()
{
    // Objective function first row
    // constraint following rows
    const std::vector<double> buffer = {
        -10, 57, 9, 24, 0, 0, 0, 1, 0,
        0.5, -5.5, -2.5, 9, 1, 0, 0, 0, 0,
        0.5, -1.5, -0.5, 1, 0, 1, 0, 0, 0,
        1, 0, 0, 0, 0, 0, 1, 0, 1
    };
    int row_dim = 4;
    int col_dim = 9;
    tableau.setBuffer(
        row_dim, col_dim, buffer
    );
    std::vector<int> basic_variables = {4, 5, 6};
    tableau.setBasicVariables(
        basic_variables
    );
    const std::map<int, std::string> variable_names = {
        {0, "x1"},
        {1, "x2"},
        {2, "x3"},
        {3, "x4"},
        {4, "s1"},
        {5, "s2"},
        {6, "s3"},
        {7, "P"},
        {8, "RHS"}
    };
    tableau.setVariableNames(
        variable_names
    );
}

void UnboundedTableauTest::SetUp()
{
    // Objective function first row
    // constraint following rows
    const std::vector<double> buffer = {
        -3, -4, 0, 0, 1, 0,
        1, -1, 1, 0, 0, 1,
        -2, 1, 0, 1, 0, 2
    };
    constexpr int row_dim = 3;
    constexpr int col_dim = 6;
    tableau.setBuffer(
        row_dim, col_dim, buffer
    );
    std::vector<int> basic_variables = {2, 3};
    tableau.setBasicVariables(
        basic_variables
    );
    const std::map<int, std::string> variable_names = {
        {0, "x1"},
        {1, "x2"},
        {2, "s1"},
        {3, "s2"},
        {4, "P"},
        {5, "RHS"}
    };
    tableau.setVariableNames(
        variable_names
    );
};

void InfeasibleTableauTest::SetUp()
{
    // Objective function first row
    // constraint following rows
    const std::vector<double> buffer = {
        -1 - BIG_M, -2 - BIG_M, -3 - BIG_M, BIG_M, 0, 0, 1, -10 * BIG_M,
        1, 1, 1, -1, 0, 1, 0, 10,
        1, 1, 1, 0, 1, 0, 0, 5
    };
    constexpr int row_dim = 3;
    constexpr int col_dim = 8;
    tableau.setBuffer(
        row_dim, col_dim, buffer
    );
    std::vector<int> basic_variables = {5, 4};
    tableau.setBasicVariables(
        basic_variables
    );
    const std::map<int, std::string> variable_names = {
        {0, "x1"},
        {1, "x2"},
        {2, "x3"},
        {3, "s1"},
        {4, "s2"},
        {5, "a1"},
        {6, "P"},
        {7, "RHS"}
    };
    tableau.setVariableNames(
        variable_names
    );
    std::vector<int> artificial_vars = {5};
    tableau.setArtificialVariables(artificial_vars);
}

void DegeneracyTableauTest::SetUp()
{
    // Objective function first row
    // constraint following rows
    const std::vector<double> buffer = {
        -6, -2, 0, 0, 1, 0,
        5, 2, 1, 0, 0, 10,
        2, 1, 0, 1, 0, 4
    };
    constexpr int row_dim = 3;
    constexpr int col_dim = 6;
    tableau.setBuffer(
        row_dim, col_dim, buffer
    );
    std::vector<int> basic_variables = {2, 3};
    tableau.setBasicVariables(
        basic_variables
    );
    const std::map<int, std::string> variable_names = {
        {0, "x1"},
        {1, "x2"},
        {2, "s1"},
        {3, "s2"},
        {4, "P"},
        {5, "RHS"}
    };
    tableau.setVariableNames(
        variable_names
    );
};

void AlternativeOptSolTableauTest::SetUp()
{
    // Objective function first row
    // constraint following rows
    const std::vector<double> buffer = {
        -4, -2, 0, 0, 1, 0,
       2, 5, 1, 0, 0, 10,
       2, 1, 0, 1, 0, 4
    };
    constexpr int row_dim = 3;
    constexpr int col_dim = 6;
    tableau.setBuffer(
        row_dim, col_dim, buffer
    );
    std::vector<int> basic_variables = {2, 3};
    tableau.setBasicVariables(
        basic_variables
    );
    const std::map<int, std::string> variable_names = {
        {0, "x1"},
        {1, "x2"},
        {2, "s1"},
        {3, "s2"},
        {4, "P"},
        {5, "RHS"}
    };
    tableau.setVariableNames(
        variable_names
    );
}