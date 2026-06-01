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
    RelationExpression operator* (double coefficient, const ColumnVector& col_vect);
    RelationExpression operator* (const ColumnVector& col_vect, double coefficient);
    //RelationExpression operator+ (double coefficient, const ColumnVector& col_vect);
    //RelationExpression operator+ (const ColumnVector& col_vect, double coefficient);
    //RelationExpression operator- (double coefficient, const ColumnVector& col_vect);
    //RelationExpression operator- (const ColumnVector& col_vect, double coefficient);
    // Column vector against column vector
    RelationExpression operator+ (const ColumnVector& col_vect_a, const ColumnVector& col_vect_b);
    RelationExpression operator- (const ColumnVector& col_vect_a, const ColumnVector& col_vect_b);
    // Column vector against RelationExpression
    RelationExpression operator+ (const ColumnVector& col_vect, const RelationExpression& lin_exp);
    RelationExpression operator- (const RelationExpression& lin_exp, const ColumnVector& col_vect);
    // RelationExpression against RelationExpression
    RelationExpression operator+ (const RelationExpression& lin_exp_a, const RelationExpression& lin_exp_b);
    RelationExpression operator- (const RelationExpression& lin_exp_a, const RelationExpression& lin_exp_b);/
    //RelationExpression operator+ (double coefficient, RelationExpression& lin_exp);
    //RelationExpression operator- (double coefficient, RelationExpression& lin_exp);
    //RelationExpression operator+ (const RelationExpression& lin_exp, double coefficient);
    //RelationExpression operator- (const RelationExpression& lin_exp, double coefficient);
    // Equality-Inequality
    RelationExpression operator>= (const ColumnVector& col_vect_a, double coefficient);
    RelationExpression operator<= (const ColumnVector& col_vect_a, double coefficient);
    RelationExpression operator== (const ColumnVector& col_vect_a, double coefficient);
    // Equality-Inequality
    RelationExpression operator>= (const RelationExpression& lin_exp, double coefficient);
    RelationExpression operator<= (const RelationExpression& lin_exp, double coefficient);
    RelationExpression operator== (const RelationExpression& lin_exp, double coefficient);
}

#endif //INC_3_LINEARPROGRAMMINGENGINE_RELATION_EXP_WRAPPER_H
