//
// Created by Martina on 01/06/2026.
//

#include "../include/column_vector.h"


namespace LPEngine
{
    ColumnVector::ColumnVector(
        const std::string& name,
        int col_id,
        ColumnRole role
        )
    {
        this->name_ = name;
        this->col_id_ = col_id;
        this->role_ = role;
    }

    void ColumnVector::addCoefficient(double coefficient)
    {
        coefficients_.push_back(coefficient);
    }
}