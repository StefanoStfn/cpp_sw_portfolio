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
                    next_state_ = State_::Reading;
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
        const std::vector<double> buffer = {
            2,1,1,0,0,0,10,
            1,1,0,1,0,0,7,
            1,2,0,0,1,0,12,
            -30,-40,0,0,0,1,0
        };
        constexpr int row_dim = 4;
        constexpr int col_dim = 7;
        tableau_.emplace();
        tableau_->overrideBuffer(
            row_dim, col_dim, buffer
        );
    }

    void SimplexMainCore::artificialVarMockStartup()
    {

    }

    void SimplexMainCore::unboundedMockStartup()
    {

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
    }

    void SimplexMainCore::checkTermination()
    {
        std::cout << "\tTerminationCheck" << std::endl;
    }

    void SimplexMainCore::executeReading()
    {
        std::cout << "\tReading" << std::endl;
    }

}
