/**
* RelationExpression storage and serialization implementation.
*
* This file implements the core container used to represent linear
* expressions, constraints, and objectives in the modeling layer. It stores
* coefficients by symbolic column name, tracks the constraint sense, and
* provides mutation helpers used during compilation. It also implements
* string/debug formatting for user-facing expressions and tableau-style
* coefficient inspection.
*/

#include "modeling/relation_expression.h"

namespace LPEngine
{
    RelationExpression::RelationExpression()
    {
        //empty Ctor
    }

    RelationExpression::RelationExpression(const std::map<std::string, double> &coefficients)
    {
        this->coefficients_ = coefficients;
    }

    void RelationExpression::setConstraintSense(ConstraintSense constraint_sense)
    {
        this->constraint_sense_ = constraint_sense;
    }

    std::string RelationExpression::toString() const
    {
        bool is_first = true;
        std::ostringstream rhs_osstring("");
        std::ostringstream oss("");
        for (auto& [key, value] : coefficients_)
        {
           if (key != RHS_KEY and key != OBJ_PROB)
           {
               if (value >= 0 && is_first)
               {
                    oss << value << "*" << key << " ";
               }
               else if (value >= 0)
               {
                   oss << "+ " << value << "*" << key << " ";
               }
               else if (value < 0 && is_first)
               {
                    oss << value << "*" << key << " ";
               }
               else if (value < 0)
               {
                   oss << "- " << value*(-1.0) << "*" << key << " ";
               }
               is_first = false;
           }
           else if (key != OBJ_PROB)
            {
                if (constraint_sense_ == ConstraintSense::Equal)
                {
                    rhs_osstring << "== " << value;
                }
                else if (constraint_sense_ == ConstraintSense::GreaterEqual)
                {
                    rhs_osstring << ">= " << value;
                }
                else if (constraint_sense_ == ConstraintSense::LessEqual)
                {
                    rhs_osstring << "<= " << value;
                }
            }
        }
        oss << rhs_osstring.str();
        return oss.str();
    }

    void RelationExpression::setCoefficient(std::string c_name, double coefficient)
    {
        if (not coefficients_.contains(c_name))
        {
            coefficients_.insert(
               {c_name, coefficient}
           );
        }
        else
        {
            coefficients_.at(c_name) = coefficient;
        }
    }
    std::string RelationExpression::toStringTable() const
    {
        std::ostringstream rhs_osstring("");
        std::ostringstream oss("");
        for (auto& [key, value] : coefficients_)
        {
            if (key != RHS_KEY and key != OBJ_PROB)
            {
                std::cout << key << " -> " << value << ", ";
            }
        }
        std::cout << "OBJ_FUNC" << " -> " << coefficients_.at(OBJ_PROB) << ", ";
        std::cout << "RHS" << " -> " << coefficients_.at(RHS_KEY);
        oss << rhs_osstring.str();
        return oss.str();
    }
}
