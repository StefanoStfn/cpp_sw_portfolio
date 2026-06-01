/**
* Implementation of the SimplexMainCore solver orchestrator.
*
* This file defines the main simplex engine workflow, including the internal
* state-machine execution, Phase II pivot dispatch, termination checks,
* final status assignment, iteration-limit handling, and solution reading.
* The engine operates on a prebuilt Tableau and delegates low-level pivot
* arithmetic to the Tableau class. It also interprets final solver outcomes,
* including optimality, unboundedness, infeasibility through artificial
* variables, degeneracy, and alternative optimal solutions.
*/

#include "../include/simplex_maincore.h"

namespace LPEngine
{
    SimplexMainCore::SimplexMainCore(
        double epsilon,
        double bigM,
        int max_iterations,
        SimplexStrategy solver_strategy
    )
    {
        this->epsilon = epsilon;
        this->bigM = bigM;
        this->max_iterations_ = max_iterations;
        this->solver_strategy_ = solver_strategy;
    }
    SimplexMainCore::SimplexMainCore(
        Tableau& tableau,
        double epsilon,
        double bigM,
        int max_iterations,
        SimplexStrategy solver_strategy
    ) : SimplexMainCore(epsilon, bigM, max_iterations, solver_strategy)
    {
        this->tableau_ = tableau;
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
                    iteration_count_++;
                    executePivotStep();
                    next_state_ = EngineState_::TerminationCheck;
                    break;
                case EngineState_::TerminationCheck:
                    checkTermination();
                    break;
                case EngineState_::Reading:
                    std::cout << "Reading" << std::endl;
                    executeReading();
                    loopCondition_ = false;
                    break;
                case EngineState_::IterationLimit:
                    std::cout << "IterationLimit" << std::endl;
                    reportIterationLimit();
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
        iteration_count_ = 0;
    }

    void SimplexMainCore::executePivotStep()
    {
        // Call the Tableau Pivot Step
        pivotResult = tableau_->executePivotStep();
        next_state_ = EngineState_::TerminationCheck;
    }

    void SimplexMainCore::checkTermination()
    {
        // Check termination is executed after every pivot step
        if (pivotResult == -1)
        {
            // -1 code: Unbounded problem
            next_state_ = EngineState_::Reading;
        }
        else if (pivotResult == 0)
        {
            auto test = tableau_->objectiveFunctionTest();
            if (iteration_count_ == max_iterations_)
            {
                next_state_ = EngineState_::IterationLimit;
            }
            else if (test == 0)
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

    void SimplexMainCore::reportIterationLimit()
    {
        status_ = SolveStatus::IterationLimitReached;
        std::cout << "\tStatus: Iteration limit reached." << std::endl;
        std::cout << "\tReason: maximum simplex iterations exceeded before convergence." << std::endl;
        std::cout << "\tIterations: " << max_iterations_ << std::endl;
        std::cout << "\tLast Entering Variable: ";
        auto col_idx = tableau_->getColIdx();
        auto var_name = tableau_->getVarName(col_idx);
        std::cout << var_name << std::endl;
        std::cout << "\tPossible cause: cycling or numerical degeneracy." << std::endl;
    }
}
