//
// Created by Martina on 31/05/2026.
//
#include <gtest/gtest.h>
#include "../include/simplex_maincore.h"

class FeasibleTableauTest : public ::testing::Test
{
    protected:
        LPEngine::Tableau tableau;
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