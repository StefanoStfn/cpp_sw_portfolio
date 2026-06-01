//
// Created by Martina on 01/06/2026.
//

#ifndef INC_3_LINEARPROGRAMMINGENGINE_COLUMN_VECTOR_H
#define INC_3_LINEARPROGRAMMINGENGINE_COLUMN_VECTOR_H

#pragma once
#include <string>
#include <vector>
#include "relation_expression.h"

namespace LPEngine
{
    enum class ColumnRole
    {
        Decision,
        Slack,
        Surplus,
        Artificial,
        Objective,
        RHS
    };

    class ColumnVector
    {
        public:
            explicit ColumnVector(
                const std::string& name,
                int col_id,
                ColumnRole role
            );
            void addCoefficient(double coefficient);

        private:
            std::string name_;
            int col_id_;
            std::vector<double> coefficients_;
            ColumnRole role_;
    };

    // Column vector interaction with coefficient
    RelationExpression operator* (double coefficient, ColumnVector& col_vect);
    RelationExpression operator+ (double coefficient, ColumnVector& col_vect);
    RelationExpression operator- (double coefficient, ColumnVector& col_vect);
    RelationExpression operator* (ColumnVector& col_vect, double coefficient);
    RelationExpression operator+ (ColumnVector& col_vect, double coefficient);
    RelationExpression operator- (ColumnVector& col_vect, double coefficient);
    // Column vector against column vector
    RelationExpression operator+ (ColumnVector& col_vect_a, ColumnVector& col_vect_b);
    RelationExpression operator- (ColumnVector& col_vect_a, ColumnVector& col_vect_b);
    // Column vector against RelationExpression
    RelationExpression operator+ (ColumnVector& col_vect, RelationExpression& lin_exp);
    RelationExpression operator- (RelationExpression& lin_exp, ColumnVector& col_vect);
    // Equality-Inequality
    RelationExpression operator>= (ColumnVector& col_vect_a, double coefficient);
    RelationExpression operator<= (ColumnVector& col_vect_a, double coefficient);
    RelationExpression operator== (ColumnVector& col_vect_a, double coefficient);
}

#endif //INC_3_LINEARPROGRAMMINGENGINE_COLUMN_VECTOR_H
