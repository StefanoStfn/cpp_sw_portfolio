//
// Created by Martina on 01/06/2026.
//

#ifndef INC_3_LINEARPROGRAMMINGENGINE_COLUMN_VECTOR_H
#define INC_3_LINEARPROGRAMMINGENGINE_COLUMN_VECTOR_H

#pragma once
#include <string>
#include <vector>

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
}

#endif //INC_3_LINEARPROGRAMMINGENGINE_COLUMN_VECTOR_H
