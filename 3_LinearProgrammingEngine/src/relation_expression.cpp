//
// Created by Martina on 01/06/2026.
//

#include "../include/relation_expression.h"

namespace LPEngine
{
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
           if (key != RHS_KEY)
           {
               if (value > 0 && is_first)
               {
                    oss << value << "*" << key << " ";
               }
               else if (value > 0)
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
           else
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
}
