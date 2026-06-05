/**
* TableauBuilder implementation for simplex canonicalization.
*
* This file converts frontend relation expressions into a simplex-compatible
* tableau layout. It moves objective terms to the left-hand side, inserts
* slack variables for <= constraints, surplus plus artificial variables for
* >= constraints, and artificial variables for equality constraints. It also
* completes missing coefficient columns with zeros, tracks initial basic
* variables through constraint metadata, and applies Big-M objective
* canonicalization so artificial basic variables start with zero reduced cost.
*/

#include "simplex/tableau_builder.h"
namespace LPEngine
{
    TableauBuilder::TableauBuilder(
        const std::vector<RelationExpression>& constraints,
        const RelationExpression& obj_function,
        const OptimizationType& optimization_type,
        int decision_variable_count,
        const std::vector<DecisionVariable>& decision_variables
    ) :
        constraints_(constraints),
        obj_function_(obj_function),
        optimization_type_(optimization_type)
    {
        // constraint + obj_function
        this->row_number_ = constraints.size() + 1;
        // decision_variable_count + __P__OBJ and RHS
        this ->column_number_ = decision_variable_count + 2;
        for (int i = 0; i < decision_variables.size(); i++)
        {
            this->decision_var_names_.push_back(
                decision_variables[i].getName()
            );
        }
    }

    void TableauBuilder::buildTableau()
    {
        moveObjectiveComponentLHS();
        insertSlackSurplusArtVarObjFactor();
        completeSlackSurplusColumns();
        completeDecisionVariableColumns();
        canonicalizeObjectiveFunction();
        std::cout << obj_function_.toStringTable() <<std::endl;
        for (int i = 0; i < constraints_.size(); i++)
        {
            std::cout << constraints_[i].toStringTable() <<std::endl;
        }
    }

    void TableauBuilder::moveObjectiveComponentLHS()
    {
        for (auto& [key,val] : obj_function_.getCoefficients())
        {
            obj_function_.setCoefficient(
                key, -val
            );
        }
    }

    void TableauBuilder::insertSlackSurplusArtVarObjFactor()
    {
        obj_function_.setCoefficient(
            OBJ_PROB, 1.0
        );
        obj_function_.setCoefficient(
            RHS_KEY, 0.0
        );
        for (int i = 0; i < constraints_.size(); i++) {
            ConstraintSense c_sense = constraints_[i].getConstraintSense();
            // Add the p component to the constraint
            constraints_[i].setCoefficient(
                OBJ_PROB, 0.0
            );
            auto coefficient_map = constraints_[i].getCoefficients();
            if (c_sense == ConstraintSense::LessEqual)
            {
                std::string name = "s" + std::to_string(ss_var_num_);
                constraints_[i].setBasicVarName(name);
                constraints_[i].setCoefficient(
                    name, 1.0
                    );
                constraints_[i].setSSIndex(ss_var_num_);
                column_number_++;
                ss_var_num_++;
            }
            else if (c_sense == ConstraintSense::GreaterEqual)
            {
                std::string name = "s" + std::to_string(ss_var_num_);
                std::string av_name = "a" + std::to_string(av_var_num_);
                constraints_[i].setBasicVarName(av_name);
                constraints_[i].setCoefficient(
                    name, -1.0
                    );
                constraints_[i].setCoefficient(
                    av_name, +1.0
                );
                obj_function_.setCoefficient(
                    av_name, BIG_M
                );
                constraints_[i].setAVIndex(av_var_num_);
                column_number_+=2;
                ss_var_num_++;
                av_var_num_++;
            }
            else if (c_sense == ConstraintSense::Equal)
            {
                std::string av_name = "a" + std::to_string(av_var_num_);
                constraints_[i].setBasicVarName(av_name);
                constraints_[i].setCoefficient(
                    av_name, +1.0
                );
                obj_function_.setCoefficient(
                    av_name, BIG_M
                );
                constraints_[i].setAVIndex(av_var_num_);
                av_var_num_++;
                column_number_++;
            }
        }
    }

    void TableauBuilder::completeSlackSurplusColumns()
    {
        // obj function
        for (int j = 0; j < ss_var_num_; j++)
        {
            std::string name = "s" + std::to_string(j);
            if (not obj_function_.getCoefficients().contains(name))
            {
                obj_function_.setCoefficient(
                   name, 0.0
               );
            }
        }
        for (int j = 0; j < av_var_num_; j++)
        {
            std::string name = "a" + std::to_string(j);
            if (not obj_function_.getCoefficients().contains(name))
            {
                obj_function_.setCoefficient(
                   name, 0.0
               );
            }
        }
        // remaining constraints
        for (int i = 0; i < constraints_.size(); i++)
        {
            auto ss_index = constraints_[i].getSSIndex();
            auto av_index = constraints_[i].getAVIndex();
            for (int j = 0; j < ss_var_num_; j++)
            {
                if (ss_index != j)
                {
                    std::string name = "s" + std::to_string(j);
                    if (not constraints_[i].getCoefficients().contains(name))
                    {
                        constraints_[i].setCoefficient(
                           name, 0.0
                       );
                    }
                }
            }
            for (int j = 0; j < av_var_num_; j++)
            {
                if (av_index != j)
                {
                    std::string name = "a" + std::to_string(j);
                    if (not constraints_[i].getCoefficients().contains(name))
                    {
                        constraints_[i].setCoefficient(
                           name, 0.0
                       );
                    }
                }
            }
        }
    }

    void TableauBuilder::completeDecisionVariableColumns()
    {
        // obj function
        for (auto& name : decision_var_names_)
        {
            bool is_present = obj_function_.getCoefficients().contains(name);
            if (!is_present)
            {
                obj_function_.setCoefficient(
                    name, 0.0
                );
            }
        }
        for (int i = 0; i < constraints_.size(); i++)
        {
            for (auto& name : decision_var_names_)
            {
                bool is_present = constraints_[i].getCoefficients().contains(name);
                if (!is_present)
                {
                    constraints_[i].setCoefficient(
                        name, 0.0
                    );
                }
            }
        }
    }

    void TableauBuilder::canonicalizeObjectiveFunction()
    {
        for (auto& constraint : constraints_)
        {
            auto av_idx = constraint.getAVIndex();
            if (av_idx != -1)
            {
                auto coeff_map = constraint.getCoefficients();
                auto obj_coeff = obj_function_.getCoefficients();
                for (auto& [key,value] : coeff_map)
                {
                    auto new_val = obj_function_.getCoefficients().at(key) - BIG_M*value;
                    obj_function_.setCoefficient(
                        key, new_val
                    );
                }
            }
        }
    }
}