//
// Created by Martina on 01/06/2026.
//

#ifndef INC_3_LINEARPROGRAMMINGENGINE_RELATION_EXP_WRAPPER_H
#define INC_3_LINEARPROGRAMMINGENGINE_RELATION_EXP_WRAPPER_H

#pragma once
#include "relation_expression.h"

namespace LPEngine
{
    // Column vector interaction with coefficient
    RelationExpression operator* (double coefficient, const DecisionVariable& d_var);
    RelationExpression operator* (const DecisionVariable& d_var, double coefficient);
    //RelationExpression operator+ (double coefficient, const DecisionVariable& d_var);
    //RelationExpression operator+ (const DecisionVariable& d_var, double coefficient);
    //RelationExpression operator- (double coefficient, const DecisionVariable& d_var);
    //RelationExpression operator- (const DecisionVariable& d_var, double coefficient);
    // unary negation
    RelationExpression operator- (const DecisionVariable& d_var);
    // Column vector against column vector
    RelationExpression operator+ (const DecisionVariable& d_var_a, const DecisionVariable& d_var_b);
    RelationExpression operator- (const DecisionVariable& d_var_a, const DecisionVariable& d_var_b);
    // Column vector against RelationExpression
    RelationExpression operator+ (const DecisionVariable& d_var, const RelationExpression& rel_exp);
    RelationExpression operator+ (const RelationExpression& rel_exp, const DecisionVariable& d_var);
    RelationExpression operator- (const DecisionVariable& d_var, const RelationExpression& rel_exp);
    RelationExpression operator- (const RelationExpression& rel_exp, const DecisionVariable& d_var);
    // RelationExpression against RelationExpression
    RelationExpression operator+ (const RelationExpression& rel_exp_a, const RelationExpression& rel_exp_b);
    RelationExpression operator- (const RelationExpression& rel_exp_a, const RelationExpression& rel_exp_b);
    RelationExpression operator* (double coefficient, const RelationExpression& rel_exp);
    RelationExpression operator* (const RelationExpression& rel_exp, double coefficient);
    // Unary Negation for RelationExpression
    RelationExpression operator- (const RelationExpression& rel_exp);
    //RelationExpression operator+ (double coefficient, RelationExpression& rel_exp);
    //RelationExpression operator- (double coefficient, RelationExpression& rel_exp);
    //RelationExpression operator+ (const RelationExpression& rel_exp, double coefficient);
    //RelationExpression operator- (const RelationExpression& rel_exp, double coefficient);
    // Equality-Inequality
    RelationExpression operator>= (const DecisionVariable& d_var_a, double coefficient);
    RelationExpression operator<= (const DecisionVariable& d_var_a, double coefficient);
    RelationExpression operator== (const DecisionVariable& d_var_a, double coefficient);
    // Equality-Inequality
    RelationExpression operator>= (const RelationExpression& rel_exp, double coefficient);
    RelationExpression operator<= (const RelationExpression& rel_exp, double coefficient);
    RelationExpression operator== (const RelationExpression& rel_exp, double coefficient);
}

#endif //INC_3_LINEARPROGRAMMINGENGINE_RELATION_EXP_WRAPPER_H
