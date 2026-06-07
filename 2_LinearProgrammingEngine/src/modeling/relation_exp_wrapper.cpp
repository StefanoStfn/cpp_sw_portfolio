/**
* Algebraic operator overload implementation for LP modeling.
*
* This file implements the arithmetic and relational operators used by the
* frontend DSL. Decision variables and relation expressions can be combined
* through addition, subtraction, scalar multiplication, and unary negation to
* create linear expressions. Constraint operators attach a RHS value and
* constraint sense to produce <=, >=, and == relation expressions. These
* overloads allow LP models to be written in natural mathematical syntax
* before being compiled into tableau form.
*/

#include "modeling/relation_exp_wrapper.h"

#include <algorithm>

namespace LPEngine
{
    // Unary negation
    RelationExpression operator- (const DecisionVariable& d_var)
    {
        auto tmp_exp = RelationExpression(
            std::map<std::string, double>{{d_var.getName(), -1.0}}
        );
        return tmp_exp;
    }
    // Column vector interaction with coefficient
    RelationExpression operator* (double coefficient, const DecisionVariable& d_var)
    {
        auto tmp_exp = RelationExpression(
            std::map<std::string, double>{{d_var.getName(), coefficient}}
        );
        return tmp_exp;
    }

    RelationExpression operator* (const DecisionVariable& d_var, double coefficient)
    {
        return coefficient * d_var;
    }

    // Column vector against column vector
    RelationExpression operator+ (const DecisionVariable& d_var_a, const DecisionVariable& d_var_b)
    {
        auto tmp_exp = RelationExpression(
            std::map<std::string, double>{
                {d_var_a.getName(), 1.0},
                {d_var_b.getName(), 1.0},
            }
        );
        return tmp_exp;
    }

    RelationExpression operator- (const DecisionVariable& d_var_a, const DecisionVariable& d_var_b)
    {
        auto tmp_exp = RelationExpression(
            std::map<std::string, double>{
                {d_var_a.getName(), 1.0},
                {d_var_b.getName(), -1.0},
            }
        );
        return tmp_exp;
    }

    // Column vector against RelationExpression
    RelationExpression operator+ (const DecisionVariable& d_var, const RelationExpression& rel_exp)
    {
        std::map<std::string, double> rel_exp_c = rel_exp.getCoefficients();
        if (rel_exp_c.contains(d_var.getName()))
        {
            rel_exp_c.at(d_var.getName()) += 1.0;
        }
        else
        {
            rel_exp_c.insert({d_var.getName(), 1.0});
        }
        auto tmp_exp = RelationExpression(rel_exp_c);
        return tmp_exp;
    }

    RelationExpression operator+ (const RelationExpression& rel_exp, const DecisionVariable& d_var)
    {
        return d_var + rel_exp;
    }

    RelationExpression operator- (const RelationExpression& rel_exp, const DecisionVariable& d_var)
    {
        std::map<std::string, double> rel_exp_c = rel_exp.getCoefficients();
        if (rel_exp_c.contains(d_var.getName()))
        {
            rel_exp_c.at(d_var.getName()) -= 1.0;
        }
        else
        {
            rel_exp_c.insert({d_var.getName(), -1.0});
        }
        auto tmp_exp = RelationExpression(rel_exp_c);
        return tmp_exp;
    }

    RelationExpression operator- (const DecisionVariable& d_var, const RelationExpression& rel_exp)
    {
        std::map<std::string, double> rel_exp_c = rel_exp.getCoefficients();
        for (auto& [key, value] : rel_exp_c)
        {
            value = -value;
        }
        if (rel_exp_c.contains(d_var.getName()))
        {
            rel_exp_c.at(d_var.getName()) += 1.0;
        }
        else
        {
            rel_exp_c.insert({d_var.getName(), 1.0});
        }
        auto tmp_exp = RelationExpression(rel_exp_c);
        return tmp_exp;
    }

    // RelationExpression against RelationExpression
    RelationExpression operator+ (const RelationExpression& rel_exp_a, const RelationExpression& rel_exp_b)
    {
        std::map<std::string, double> rel_a_exp_c = rel_exp_a.getCoefficients();
        std::map<std::string, double> rel_b_exp_c = rel_exp_b.getCoefficients();
        for (auto& [key, value] : rel_a_exp_c)
        {
            if (rel_b_exp_c.contains(key))
            {
                rel_b_exp_c.at(key) += value;
            }
            else
            {
                rel_b_exp_c.insert({key, value});
            }
        }
        auto tmp_exp = RelationExpression(rel_b_exp_c);
        return tmp_exp;
    }

    RelationExpression operator- (const RelationExpression& rel_exp_a, const RelationExpression& rel_exp_b)
    {
        std::map<std::string, double> rel_a_exp_c = rel_exp_a.getCoefficients();
        std::map<std::string, double> rel_b_exp_c = rel_exp_b.getCoefficients();
        for (auto& [key, value] : rel_b_exp_c)
        {
            if (rel_a_exp_c.contains(key))
            {
                rel_a_exp_c[key] -= value;
            }
            else
            {
                rel_a_exp_c.insert({key, -value});
            }
        }
        auto tmp_exp = RelationExpression(rel_a_exp_c);
        return tmp_exp;
    }


    RelationExpression operator* (double coefficient, const RelationExpression& rel_exp)
    {
        std::map<std::string, double> rel_exp_c = rel_exp.getCoefficients();
        for (auto& [key, value] : rel_exp_c)
        {
            value *= coefficient;
        }
        auto tmp_exp = RelationExpression(rel_exp_c);
        return tmp_exp;
    }
    RelationExpression operator* (const RelationExpression& rel_exp, double coefficient)
    {
        std::map<std::string, double> rel_exp_c = rel_exp.getCoefficients();
        for (auto& [key, value] : rel_exp_c)
        {
            value *= coefficient;
        }
        auto tmp_exp = RelationExpression(rel_exp_c);
        return tmp_exp;
    }

    // Unary Negation for RelationExpression
    RelationExpression operator- (const RelationExpression& rel_exp)
    {
        std::map<std::string, double> rel_exp_c = rel_exp.getCoefficients();
        for (auto& [key, value] : rel_exp_c)
        {
            value = -value;
        }
        auto tmp_exp = RelationExpression(rel_exp_c);
        return tmp_exp;
    }

    // Equality-Inequality
    RelationExpression operator>= (const DecisionVariable& d_var, double coefficient)
    {
        auto tmp_exp = RelationExpression(
            std::map<std::string, double>{{d_var.getName(), 1.0}}
            );
        std::map<std::string, double> rel_exp_c = tmp_exp.getCoefficients();
        if (rel_exp_c.contains(RHS_KEY))
        {
            throw std::invalid_argument(
                "Interaction with multiple RHS terms."
            );
        }
        tmp_exp.setCoefficient(RHS_KEY, coefficient);
        tmp_exp.setConstraintSense(ConstraintSense::GreaterEqual);
        return tmp_exp;
    }

    RelationExpression operator<= (const DecisionVariable& d_var, double coefficient)
    {
        auto tmp_exp = RelationExpression(
            std::map<std::string, double>{{d_var.getName(), 1.0}}
            );
        std::map<std::string, double> rel_exp_c = tmp_exp.getCoefficients();
        if (rel_exp_c.contains(RHS_KEY))
        {
            throw std::invalid_argument(
                "Interaction with multiple RHS terms."
            );
        }
        tmp_exp.setCoefficient(RHS_KEY, coefficient);
        tmp_exp.setConstraintSense(ConstraintSense::LessEqual);
        return tmp_exp;
    }

    RelationExpression operator== (const DecisionVariable& d_var, double coefficient)
    {
        auto tmp_exp = RelationExpression(
            std::map<std::string, double>{{d_var.getName(), 1.0}}
            );
        std::map<std::string, double> rel_exp_c = tmp_exp.getCoefficients();
        if (rel_exp_c.contains(RHS_KEY))
        {
            throw std::invalid_argument(
                "Interaction with multiple RHS terms."
            );
        }
        tmp_exp.setCoefficient(RHS_KEY, coefficient);
        tmp_exp.setConstraintSense(ConstraintSense::Equal);
        return tmp_exp;
    }

    RelationExpression operator>= (const RelationExpression& rel_exp, double coefficient)
    {
        std::map<std::string, double> rel_exp_c = rel_exp.getCoefficients();
        if (rel_exp_c.contains(RHS_KEY))
        {
            throw std::invalid_argument(
                "Interaction with multiple RHS terms."
            );
        }
        rel_exp_c.insert({RHS_KEY, coefficient});
        auto tmp_exp = RelationExpression(rel_exp_c);
        tmp_exp.setConstraintSense(ConstraintSense::GreaterEqual);
        return tmp_exp;
    }

    RelationExpression operator<= (const RelationExpression& rel_exp, double coefficient)
    {
        std::map<std::string, double> rel_exp_c = rel_exp.getCoefficients();
        if (rel_exp_c.contains(RHS_KEY))
        {
            throw std::invalid_argument(
                "Interaction with multiple RHS terms."
            );
        }
        rel_exp_c.insert({RHS_KEY, coefficient});
        auto tmp_exp = RelationExpression(rel_exp_c);
        tmp_exp.setConstraintSense(ConstraintSense::LessEqual);
        return tmp_exp;
    }

    RelationExpression operator== (const RelationExpression& rel_exp, double coefficient)
    {
        std::map<std::string, double> rel_exp_c = rel_exp.getCoefficients();
        if (rel_exp_c.contains(RHS_KEY))
        {
            throw std::invalid_argument(
                "Interaction with multiple RHS terms."
            );
        }
        rel_exp_c.insert({RHS_KEY, coefficient});
        auto tmp_exp = RelationExpression(rel_exp_c);
        tmp_exp.setConstraintSense(ConstraintSense::Equal);
        return tmp_exp;
    }
}
