 //
// Created by Martina on 27/05/2026.
//

#include "../include/simplex_maincore.h"



namespace LPEngine
{

    SimplexMainCore::SimplexMainCore(double epsilon, double bigM)
    {
        this->epsilon = epsilon;
        this->bigM = bigM;
    }

    SimplexMainCore::SimplexMainCore(
        Tableau& tableau,
        double epsilon,
        double bigM
    )
    {
        this->tableau_ = tableau;
        this->epsilon = epsilon;
        this->bigM = bigM;
    }

    void SimplexMainCore::startEngine()
    {
        // Main State Machine
        while (loopCondition_)
        {
            present_state_ = next_state_;

            switch (present_state_)
            {
                case EngineState_::PhaseII:
                    std::cout << "PhaseII" << std::endl;
                    executePivotStep();
                    next_state_ = EngineState_::TerminationCheck;
                    break;
                case EngineState_::TerminationCheck:
                    std::cout << "TerminationCheck" << std::endl;
                    checkTermination();
                    break;
                case EngineState_::Reading:
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

    void SimplexMainCore::resetEngine()
    {
        // Reset the Variables for new runs
        present_state_ = EngineState_::PhaseII;
        next_state_ = EngineState_::PhaseII;
        loopCondition_ = true;
        pivotResult = 0;
        tableau_->reset();
        degeneracy_ = false;
        alternative_sol_ = false;
        status_ = SolveStatus::NotStarted;
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
        const std::map<int, std::string> variable_names = {
            {0, "x"},
            {1, "y"},
            {2, "s1"},
            {3, "s2"},
            {4, "s3"},
            {5, "P"},
            {6, "RHS"}
        };
        tableau_->overrideVariableNames(
            variable_names
        );
    }

    void SimplexMainCore::unboundedMockStartup()
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
        tableau_.emplace();
        tableau_->overrideBuffer(
            row_dim, col_dim, buffer
            );
        std::vector<int> basic_variables = {2, 3};
        tableau_->overrideBasicVariables(
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
        tableau_->overrideVariableNames(
            variable_names
        );
    }

    void SimplexMainCore::unfeasibleMockStartup()
    {
        // Objective function first row
        // constraint following rows
        const std::vector<double> buffer = {
            -1 - bigM, -2 - bigM, -3 - bigM, bigM, 0, 0, 1, -10 * bigM,
            1, 1, 1, -1, 0, 1, 0, 10,
            1, 1, 1, 0, 1, 0, 0, 5
        };
        constexpr int row_dim = 3;
        constexpr int col_dim = 8;
        tableau_.emplace();
        tableau_->overrideBuffer(
            row_dim, col_dim, buffer
        );
        std::vector<int> basic_variables = {5, 4};
        tableau_->overrideBasicVariables(
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
        tableau_->overrideVariableNames(
            variable_names
        );
        std::vector<int> artificial_vars = {5};
        tableau_->overrideArtificialVariables(artificial_vars);
    }

    void SimplexMainCore::degeneracyMockStartup()
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
        tableau_.emplace();
        tableau_->overrideBuffer(
            row_dim, col_dim, buffer
        );
        std::vector<int> basic_variables = {2, 3};
        tableau_->overrideBasicVariables(
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
        tableau_->overrideVariableNames(
            variable_names
        );
    }

    void SimplexMainCore::alternativeOptSolMockStartup()
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
        tableau_.emplace();
        tableau_->overrideBuffer(
            row_dim, col_dim, buffer
        );
        std::vector<int> basic_variables = {2, 3};
        tableau_->overrideBasicVariables(
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
        tableau_->overrideVariableNames(
            variable_names
        );
    }

    void SimplexMainCore::executePivotStep()
    {
        // Call the Tableau Pivot Step
        std::cout << "\tPivot Step" << std::endl;
        pivotResult = tableau_->executePivotStep();
        next_state_ = EngineState_::TerminationCheck;
    }



    void SimplexMainCore::checkTermination()
    {
        // Check termination is executed after every pivot step
        std::cout << "\tTerminationCheck" << std::endl;
        if (pivotResult == -1)
        {
            // -1 code: Unbounded problem
            next_state_ = EngineState_::Reading;
        }
        else if (pivotResult == 0)
        {
            auto test = tableau_->objectiveFunctionTest();
            if (test == 0)
            {
                next_state_ = EngineState_::Reading;
            }
            else if (test == -1)
            {
                next_state_ = EngineState_::PhaseII;
            }
        }
    }

    void SimplexMainCore::printFeasibleSolution(std::vector<int>& basic_variables)
    {
        // Used for formatting the feasible solution printing
        std::cout << "\tStatus: Feasible Optimal Solution Reached." << std::endl;
        std::cout << "\tOptimal Solution RHS: " ;
        std::cout << tableau_->getObjFunctionRHS() << std::endl ;
        printReading(basic_variables);
        if (degeneracy_)
        {
            std::cout << "\tDegenerate solution: true" << std::endl ;
        }
        if (alternative_sol_)
        {
            std::cout << "\tAlternative solution: true" << std::endl ;
        }

    }

    void SimplexMainCore::executeReading()
    {
        //  0  Optimal
        // -1  Infeasible
        // -2  Unbounded
        // -3  IterationLimitReached
        std::vector<int> basic_variables = tableau_->getBasicVariables();
        if (pivotResult == -1)
        {
            std::cout << "\tStatus: Unbounded" << std::endl;
            std::cout << "\tReason: entering column has no valid leaving row" << std::endl;
            int col_id = tableau_->getColIdx();
            std::cout << "\tEntering variable column: ";
            std::cout << tableau_->getVarName(col_id) << std::endl;
            status_ = SolveStatus::Unbounded;
        }
        else if (pivotResult == 0)
        {
            if (artificialVariableCheck())
            {
                status_ = SolveStatus::Optimal;
                alternativeSolutionsCheck(basic_variables);
                printFeasibleSolution(basic_variables);
            }
            else
            {
                status_ = SolveStatus::Infeasible;
                std::cout << "\tStatus: Infeasible." << std::endl;
                std::cout << "\tReason: artificial variable remains positive" << std::endl;
                printReading(basic_variables);
            }
        }
    }

    void SimplexMainCore::printReading(
        std::vector<int>& basic_variables
    )
    {
        // Prints the variables and corresponding values
        int col_num = tableau_->getColNum();
        double rhs;
        for (int i = 0; i < col_num-2; i++)
        {
            bool is_basic = std::find(
                basic_variables.begin(),
                basic_variables.end(),
                i
                ) != basic_variables.end();
            if (is_basic)
            {
                std::cout << "\t" << tableau_->getVarName(i);
                rhs = tableau_->getRHS(i);
                std::cout << "\t" << rhs << std::endl ;
                if (std::abs(rhs) < epsilon)
                {
                    degeneracy_ = true;
                }
            }
            else
            {
                std::cout << "\t" << tableau_->getVarName(i);
                std::cout << "\t0" << std::endl ;
            }
        }
    }

    bool SimplexMainCore::artificialVariableCheck() const
    {
        // check if artificial variables are not basic variables
        // and if they are Basic one they rhs is lower than eps
        auto a_variables = tableau_->getArtificialVariables();
        std::vector<int> a_check(a_variables.size(), 0);
        for (int i = 0; i < a_variables.size(); i++)
        {
            bool is_basic = std::find(
                a_variables.begin(),
                a_variables.end(),
                a_variables[i] ) != a_variables.end();
            if (is_basic and tableau_->getRHS(a_variables[i]) > epsilon)
            {
                return false;
            }
        }
        return true;
    }

    void SimplexMainCore::alternativeSolutionsCheck(std::vector<int>& basic_variables)
    {
        // check the multiplying coefficient for the variables
        // that are non-basic variables when algorithms terminates
        int col_num = tableau_->getColNum();
        for (int i = 0; i < col_num-2; i++)
        {
            bool is_basic = std::find(
                basic_variables.begin(),
                basic_variables.end(),
                i ) != basic_variables.end();
            if (!is_basic and std::abs(tableau_->getObjectiveFuncCoefficient(i)) < epsilon)
            {
                alternative_sol_ = true;
            }
        }
    }

    double SimplexMainCore::getOptimaSolutionRHS() const
    {
        return tableau_->getObjFunctionRHS();
    }

    std::map<std::string, double> SimplexMainCore::getVariableValues()
    {
        std::map<std::string, double> variable_values;
        auto basic_variables = tableau_->getBasicVariables();
        int col_num = tableau_->getColNum();
        double rhs;
        for (int i = 0; i < col_num-2; i++)
        {
            bool is_basic = std::find(
                basic_variables.begin(),
                basic_variables.end(),
                i
                ) != basic_variables.end();
            if (is_basic)
            {
                rhs = tableau_->getRHS(i);
                if (std::abs(rhs) < epsilon)
                {
                    variable_values.insert(
                        {tableau_->getVarName(i), 0.0}
                    );
                }
                else
                {
                    variable_values.insert(
                        {tableau_->getVarName(i), tableau_->getRHS(i)}
                    );
                }
            }
            else
            {
                variable_values.insert(
                    {tableau_->getVarName(i), 0.0}
                );
            }
        }
        return variable_values;
    }

}
