/**
* Public solver interface and frontend-to-backend orchestration.
*
* This file implements the user-facing LP solver API: variable creation,
* constraint registration, objective setup, compilation, and execution.
* It owns the translation from modeling expressions into the internal
* simplex-ready representation, including variable ordering, RHS sign
* normalization, slack/surplus/artificial variable indexing, Big-M metadata,
* basis initialization, and flattened tableau buffer construction. It also
* dispatches the selected solver backend, collects final status flags, and
* exposes solution values through the public API.
*/

#include "interface/lp_solver.h"

namespace LPEngine
{
    LPSolver::LPSolver(
        SolverStrategy strategy,
        SimplexStrategy solver_strategy,
        double epsilon,
        double bigM,
        int max_iterations
    )
    {
        this->strategy_ = strategy;
        this->solver_strategy_ = solver_strategy;
        this->epsilon_ = epsilon;
        this->bigM_ = bigM;
        this->max_iterations_ = max_iterations;
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
        if (constraint.getConstraintSense() == ConstraintSense::Reset)
        {
            throw std::invalid_argument(
                "Create a constraint for the linear expression using ==, <=, >=."
            );
        }
        constraints_.push_back(constraint);
        std::cout << "Constraint is added:\n\t" << constraint.toString() << std::endl;
    }

    void LPSolver::addObjectiveFunction(
        const RelationExpression& objective,
        OptimizationType opt_type
    )
    {
        if (objective_.getHasObjective())
        {
            throw std::invalid_argument(
                "Multiple objective functions are not supported"
            );
        }
        if (objective.getConstraintSense() != ConstraintSense::Reset)
        {
            throw std::invalid_argument(
                "Obj Function cannot be an inequality-equality expression"
            );
        }
        this ->objective_ = objective;
        this->objective_.setHasObjective();
        this->opt_type_ = opt_type;
        std::cout << "Objective Function is added:" << std::endl;
        if (opt_type == OptimizationType::Maximize)
        {
            std::cout << "\tMaximize ";
            std::cout << this->objective_.toString() << std::endl;
        }
        else if (opt_type == OptimizationType::Minimize)
        {
            std::cout << "\tMinimize ";
            std::cout << this->objective_.toString() << std::endl;
            for (auto& [key, value] : objective_.getCoefficients())
            {
                objective_.setCoefficient(
                    key, -value
                );
            }
        }
    }

    void LPSolver::addObjectiveFunction(const DecisionVariable &objective, OptimizationType opt_type)
    {
        addObjectiveFunction(
            1*objective,
            opt_type
        );
    }

    void LPSolver::compileSolver()
    {
        sanityCheck();
        std::cout << "Sanity Check Passed!" << std::endl;
        switch (strategy_)
        {
            case SolverStrategy::Simplex:
                runSimplexBuilding();
                break;
            case SolverStrategy::InteriorPoint:
                runInteriorPointBuilding();
                break;
        }
    }

    void LPSolver::runSolver()
    {
        switch (strategy_)
        {
            case SolverStrategy::Simplex:
                // build the Tableau and run the problem
                std::cout << "Engine is Running..." << std::endl;
                buildRunSimplexSolver(
                    t_builder_->getRowNumber(),
                    t_builder_->getColNumber()
                );
            break;
        case SolverStrategy::InteriorPoint:
            runInteriorPointBuilding();
            break;
        }   
    }

    void LPSolver::run()
    {
        compileSolver();
        runSolver();
    }

    double LPSolver::getOptimaSolutionRHS() const
    {
        switch (strategy_)
        {
            case SolverStrategy::Simplex:
                if (opt_type_ == OptimizationType::Minimize)
                {
                    return simplex_maincore_->getOptimaSolutionRHS() * (-1.0);
                }
                return simplex_maincore_->getOptimaSolutionRHS();
            case SolverStrategy::InteriorPoint:
                return 0.0;
            default:
                return 0.0;
        }
    }

    std::map<std::string, double> LPSolver::getVariableValues()
    {
        std::map<std::string,double> variable_values;
        switch (strategy_)
        {
            case SolverStrategy::Simplex:
                return simplex_maincore_->getVariableValues();
            case SolverStrategy::InteriorPoint:
                return variable_values;
            default:
                return variable_values;
        }
    }


    void LPSolver::sanityCheck()
    {
        if (!objective_.getHasObjective())
        {
            throw std::invalid_argument(
                "Cannot solve LP: objective function is missing."
            );
        }
        if (constraints_.empty())
        {
            throw std::invalid_argument(
                "Cannot solve LP: no constraints have been added."
            );
        }
    }

    void LPSolver::runSimplexBuilding()
    {
        std::cout << "Running Simplex Algorithm" << std::endl;
        // Create Variable Structure
        t_builder_.emplace(
            constraints_,
            objective_,
            opt_type_,
            this->getDecisionVariableCount(),
            decision_variables_
        );
        std::cout << "Building Tableau Table..." << std::endl;
        t_builder_->buildTableau();
        auto ss_num = t_builder_->getSSNumber();
        auto c_init_size = column_name_map_.size();
        auto av_num = t_builder_->getAVNumber();
        defineRepresentationOrder(
            ss_num, c_init_size, av_num
        );
        // build Tableau variable dependency
        constraints_ = t_builder_->getConstraints();
        objective_ = t_builder_->getObjective();
        for (int i = 0; i < t_builder_->getAVNumber(); i++)
        {
            auto av_name = "a" + std::to_string(i);
            artificial_variables_.push_back(
                column_name_map_.at(av_name)
            );
        }
        // Build the buffer
        buildBasicVarVect();
        standardizeSigns();
        buildBuffer();
    }
    void LPSolver::defineRepresentationOrder(int ss_num, int c_init_size, int av_num)
    {
        for (const auto& pair : column_name_map_)
        {
            var_order_.push_back(pair.first);
        }
        for (int i = 0; i < ss_num; i++)
        {
            auto name = "s" + std::to_string(i);
            auto index = i + c_init_size;
            column_name_map_.insert(
                {name, index}
            );
            var_order_.push_back(name);
        }
        for (int i = 0; i < av_num; i++)
        {
            auto name = "a" + std::to_string(i);
            auto index = i + c_init_size + ss_num;
            column_name_map_.insert(
                {name, index}
            );
            var_order_.push_back(name);
        }
        var_order_.push_back(OBJ_PROB);
        column_name_map_.insert(
            {OBJ_PROB, static_cast<int>(var_order_.size()-1)}
        );
        var_order_.push_back(RHS_KEY);
        column_name_map_.insert(
            {RHS_KEY, static_cast<int>(var_order_.size()-1)}
        );
    }

    void LPSolver::buildBasicVarVect()
    {
        for (const auto& constraint : constraints_)
        {
            auto b_var = constraint.getBasicVarName();
            basic_variables_.push_back(
                column_name_map_.at(b_var)
            );
        }
    }

    void LPSolver::standardizeSigns()
    {
        for (auto& constraint : constraints_)
        {
            auto c_coeffs = constraint.getCoefficients();
            if (c_coeffs.at(RHS_KEY) < 0)
            {
                for (auto& [key, value] : c_coeffs)
                {
                    constraint.setCoefficient(
                        key, -value
                    );
                }
                if (constraint.getConstraintSense() == ConstraintSense::GreaterEqual)
                {
                    constraint.setConstraintSense(ConstraintSense::LessEqual);
                }
                else if (constraint.getConstraintSense() == ConstraintSense::LessEqual)
                {
                    constraint.setConstraintSense(ConstraintSense::GreaterEqual);
                }
            }
        }
    }

    void LPSolver::buildBuffer()
    {
        auto obj_coeffs = objective_.getCoefficients();
        for (auto& name : var_order_)
        {
            buffer_.push_back(
                obj_coeffs.at(name)
            );
        }
        for (auto& constraint : constraints_)
        {
            auto c_coeffs = constraint.getCoefficients();
            for (auto& name : var_order_)
            {
                buffer_.push_back(
                    c_coeffs.at(name)
                );
            }
        }
    }

    void LPSolver::buildRunSimplexSolver(int row_num, int col_num)
    {
        std::map<int, std::string> variable_names;
        for (int i = 0; i < var_order_.size(); i++)
        {
            variable_names.insert({i, var_order_[i]});
        }
        // Instantiate SimplexMainCore
        auto tableau = Tableau(
            SimplexStrategy::BlandRule
        );
        tableau.setBuffer(
            row_num,
            col_num,
            this->buffer_
        );
        tableau.setBasicVariables(basic_variables_);
        tableau.setVariableNames(variable_names);
        tableau.setArtificialVariables(artificial_variables_);
        simplex_maincore_.emplace(
            tableau,
            opt_type_,
            solver_strategy_,
            epsilon_,
            bigM_,
            max_iterations_
        );
        simplex_maincore_->startEngine();
        status_ = simplex_maincore_->getStatus();
        alternative_sol_ = simplex_maincore_->isAlternativeSolution();
        degeneracy_ = simplex_maincore_->isDegenerateSolution();
    }

    //
    // Interior Point Specific (V2?)
    //

    void LPSolver::runInteriorPointBuilding()
    {
        // Code
    }
}