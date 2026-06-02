//
// Created by Martina on 01/06/2026.
//

#include "../include/lp_solver.h"

namespace LPEngine
{
    LPSolver::LPSolver(SolverStrategy strategy)
    {
        this->strategy_ = strategy;
    }

    DecisionVariable& LPSolver::addVariable(const std::string& var_name)
    {
        bool is_present = column_name_map_.contains(
            var_name
        );
        if (!is_present)
        {
            auto new_decision_variable = DecisionVariable(var_name, col_id_counter);
            decision_variables_.push_back(new_decision_variable);
            column_name_map_.insert(
                {var_name, col_id_counter}
            );
            col_id_counter++;
            return decision_variables_.at(col_id_counter-1);
        }
        throw std::invalid_argument(
            "Decision Variables cannot be added multiple times"
        );
    }

    void LPSolver::addConstraint(const RelationExpression& constraint)
    {
        // Received constraint
        std::cout << "Constraint is added" << std::endl;
    }

    void LPSolver::addObjectiveFunction()
    {

    }

    void LPSolver::solve()
    {
        switch (strategy_)
        {
            case SolverStrategy::Simplex:
                runSimplex();
                break;
            case SolverStrategy::InteriorPoint:
                runInteriorPoint();
                break;
        }
    }

    void LPSolver::runSimplex()
    {
        // Create Tableau
        // Instantiate SimplexMainCore
        // run engine
    }

    void LPSolver::runInteriorPoint()
    {
        // Code
    }
}