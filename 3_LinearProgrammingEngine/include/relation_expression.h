//
// Created by Martina on 01/06/2026.
//

#ifndef INC_3_LINEARPROGRAMMINGENGINE_RELATION_EXPRESSION_H
#define INC_3_LINEARPROGRAMMINGENGINE_RELATION_EXPRESSION_H

#pragma once
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include "decision_variable.h"

#define RHS_KEY "RHS"

namespace LPEngine
{
    enum class ConstraintSense
    {
        Reset,
        Equal,
        GreaterEqual,
        LessEqual
    };

    class RelationExpression
    {
        public:
            explicit RelationExpression(const std::map<std::string, double> &coefficients);
            const std::map<std::string, double>& getCoefficients() const {return coefficients_;}
            void setConstraintSense(ConstraintSense constraint_sense);
            ConstraintSense getConstraintSense() const {return constraint_sense_;};
            std::string toString() const;
        private:
            std::map<std::string, double> coefficients_;
            ConstraintSense constraint_sense_ = ConstraintSense::Reset;
    };
}


#endif //INC_3_LINEARPROGRAMMINGENGINE_RELATION_EXPRESSION_H
