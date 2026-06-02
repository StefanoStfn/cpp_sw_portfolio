/**
* GoogleTest fixtures for SimplexMainCore integration tests.
*
* These fixtures initialize representative simplex tableau for the main
* solver outcomes: feasible optimality, unboundedness, infeasibility,
* degeneracy, alternative optimal solutions, and cycling/anti-cycling
* behavior. Each fixture prepares the tableau buffer, initial basis,
* variable-name metadata, and artificial-variable metadata when required.
* The fixtures are intended for engine-level tests, where the full simplex
* workflow is exercised from an already-built tableau, not for testing LP
* preprocessing or tableau construction from user-facing model definitions.
*/

#ifndef INC_3_LINEARPROGRAMMINGENGINE_SIMPLEX_FIXTURES_H
#define INC_3_LINEARPROGRAMMINGENGINE_SIMPLEX_FIXTURES_H
#pragma once
#include <gtest/gtest.h>
#include "../../include/tableau.h"

class FeasibleTableauTest : public ::testing::Test
{
    protected:
        LPEngine::Tableau tableau = LPEngine::Tableau(
            LPEngine::SimplexStrategy::MostNegative
        );
        void SetUp() override;
};

class FractionalValueTableauTest : public ::testing::Test
{
    protected:
        LPEngine::Tableau tableau = LPEngine::Tableau(
            LPEngine::SimplexStrategy::MostNegative
        );
        void SetUp() override;
};

class CycleFeasibleTableauTest : public ::testing::Test
{
    protected:
        LPEngine::Tableau tableau = LPEngine::Tableau(
            LPEngine::SimplexStrategy::BlandRule
        );
        void SetUp() override;
};

class IterationLimitTableauTest : public ::testing::Test
{
    protected:
        LPEngine::Tableau tableau = LPEngine::Tableau(
            LPEngine::SimplexStrategy::MostNegative
        );
        void SetUp() override;
};

class UnboundedTableauTest : public ::testing::Test
{
    protected:
        LPEngine::Tableau tableau;
        void SetUp() override;
};

class InfeasibleTableauTest : public ::testing::Test
{
    protected:
        LPEngine::Tableau tableau;
        double bigM = 1E6;
        void SetUp() override;
};

class DegeneracyTableauTest : public ::testing::Test
{
    protected:
        LPEngine::Tableau tableau;
        void SetUp() override;
};

class AlternativeOptSolTableauTest : public ::testing::Test
{
    protected:
        LPEngine::Tableau tableau;
        void SetUp() override;
};
#endif //INC_3_LINEARPROGRAMMINGENGINE_SIMPLEX_FIXTURES_H
