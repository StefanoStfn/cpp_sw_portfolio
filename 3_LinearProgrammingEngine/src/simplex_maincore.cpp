 //
// Created by Martina on 27/05/2026.
//

#include "../include/simplex_maincore.h"

#include <stdexcept>
#include <iostream>

namespace LPEngine
{

    SimplexMainCore::SimplexMainCore()
    {
        //ctor
    }

    void SimplexMainCore::startEngine()
    {
        while (loopCondition_)
        {
            present_state_ = next_state_;

            switch (present_state_)
            {
                case State_::PhaseII:
                    std::cout << "PhaseII" << std::endl;
                    executePivotStep();
                    next_state_ = State_::TerminationCheck;
                    break;
                case State_::TerminationCheck:
                    std::cout << "TerminationCheck" << std::endl;
                    checkTermination();
                    break;
                case State_::Reading:
                    std::cout << "Reading" << std::endl;
                    executeReading();
                    loopCondition_ = false;
                    break;
                default:
                    throw std::invalid_argument(
                        "Invalid State"
                    );
            }
        }
    }

    void SimplexMainCore::feasibleMockStartup()
    {
        // Objective function first row
        // constraint following rows
        const std::vector<double> buffer = {
            -30, -40, 0, 0, 0, 1, 0,
            2, 1, 1, 0, 0, 0, 10,
            1, 1, 0, 1, 0, 0, 7,
            1, 2, 0, 0, 1, 0, 12
        };
        constexpr int row_dim = 4;
        constexpr int col_dim = 7;
        tableau_.emplace();
        tableau_->overrideBuffer(
            row_dim, col_dim, buffer
        );
        std::vector<int> basic_variables = {2, 3, 4};
        tableau_->overrideBasicVariables(
            basic_variables
        );
    }

    void SimplexMainCore::artificialVarMockStartup()
    {

    }

    void SimplexMainCore::unboundedMockStartup()
    {
        // Objective function first row
        // constraint following rows
        const std::vector<double> buffer = {
            -3, -4, 0, 0, 1, 0,
            1, -1, 1, 0, 0, 1,
            -2, -1, 0, 1, 0, 2
        };
        constexpr int row_dim = 3;
        constexpr int col_dim = 6;
        tableau_.emplace();
        tableau_->overrideBuffer(
            row_dim, col_dim, buffer
        );
    }

    void SimplexMainCore::unfeasibleMockStartup()
    {

    }

    void SimplexMainCore::degeneracyMockStartup()
    {

    }

    void SimplexMainCore::alternativeOptSolMockStartup()
    {

    }

    void SimplexMainCore::executePivotStep()
    {
        std::cout << "\tPivot Step" << std::endl;
        pivotResult = tableau_->executePivotStep();
        next_state_ = State_::TerminationCheck;
    }



    void SimplexMainCore::checkTermination()
    {
        std::cout << "\tTerminationCheck" << std::endl;
        if (pivotResult == -1)
        {
            // -1 code: Unbounded problem
            next_state_ = State_::Reading;
        }
        else if (pivotResult == 0)
        {
            auto test = tableau_->objectiveFunctionTest();
            if (test == 0)
            {
                next_state_ = State_::Reading;
            }
            else if (test == -1)
            {
                next_state_ = State_::PhaseII;
            }
        }
    }

    void SimplexMainCore::executeReading()
    {
        if (pivotResult == -1)
        {
            std::cout << "\tUnbounded Solution" << std::endl;
        }
        else if (pivotResult == 0)
        {
            std::vector<int> basic_variables = tableau_->getBasicVariables();
            std::cout << "\tFeasible Optimal Solution Reached." << std::endl;
            std::cout << "\tOptimal Solution RHS: " ;
            std::cout << tableau_->getObjFunctionRHS() << std::endl ;
            for (int i = 0; i < basic_variables.size(); i++)
            {
                std::cout << "\t" << "Variable " << basic_variables[i];
                std::cout << "\t" << tableau_->getRHS(basic_variables[i]) << std::endl ;
            }
        }
    }

}
