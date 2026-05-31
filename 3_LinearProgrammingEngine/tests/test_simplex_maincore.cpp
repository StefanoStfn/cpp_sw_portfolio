//
// Created by Martina on 31/05/2026.
//
#include <gtest/gtest.h>
#include "../include/simplex_maincore.h"

class FeasibleTableauTest : public ::testing::Test
{
    protected:
        LPEngine::Tableau feasible_tableau;
        LPEngine::Tableau beale_cycle_feasible_tableau;
        // Objective function first row
        // constraint following rows
        void SetUp() override
        {
            // Basic Feasible Example
            const std::vector<double> buffer = {
                -30, -40, 0, 0, 0, 1, 0,
                2, 1, 1, 0, 0, 0, 10,
                1, 1, 0, 1, 0, 0, 7,
                1, 2, 0, 0, 1, 0, 12
            };
            int row_dim = 4;
            int col_dim = 7;
            feasible_tableau.overrideBuffer(
                row_dim, col_dim, buffer
            );
            std::vector<int> basic_variables = {2, 3, 4};
            feasible_tableau.overrideBasicVariables(
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
            feasible_tableau.overrideVariableNames(
                variable_names
            );
            // Beale cycling example
            const std::vector<double> bc_buffer = {
                -10, 57, 9, 24, 0, 0, 0, 1, 0,
                0.5, -5.5, -2.5, 9, 1, 0, 0, 0, 0,
                0.5, -1.5, -0.5, 1, 0, 1, 0, 0, 0,
                1, 0, 0, 0, 0, 0, 1, 0, 1
            };
            int bc_row_dim = 4;
            int bc_col_dim = 9;
            beale_cycle_feasible_tableau.overrideBuffer(
                bc_row_dim, bc_col_dim, bc_buffer
            );
            std::vector<int> bc_basic_variables = {4, 5, 6};
            beale_cycle_feasible_tableau.overrideBasicVariables(
                bc_basic_variables
            );
            const std::map<int, std::string> bc_variable_names = {
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
            beale_cycle_feasible_tableau.overrideVariableNames(
                bc_variable_names
            );
        }
};