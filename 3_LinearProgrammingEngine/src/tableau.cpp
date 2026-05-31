//
// Created by Martina on 27/05/2026.
//

#include <stdexcept>
#include <algorithm>

#include "../include/tableau.h"

#include <numeric>


namespace LPEngine {
    Tableau::Tableau()
    {
        //ctor
    }

    void Tableau::reset()
    {
        // Vector clearing
        basic_variables_.clear();
        variable_names_.clear();
        artificial_variables_.clear();
        tableau_buffer_.clear();
        // Simple Variable clearing
        row_number_ = 0;
        column_number_ = 0;
        colIdx = 0;
        minRatioRowIndex = 0;
        minRatio = -1.0;
    }

    void Tableau::overrideBuffer(const int row, const int column, const std::vector<double> &buffer)
    {
        row_number_ = row;
        column_number_ = column;
        if (row * column != buffer.size())
        {
            throw std::invalid_argument(
                "Rows and Columns should be compliant with the Buffer Dimension")
            ;
        }
        tableau_buffer_ = buffer;
    }
    void Tableau::overrideBasicVariables(const std::vector<int> &basic_v)
    {
        if (basic_v.size() != row_number_-1)
        {
            throw std::invalid_argument(
                "overrideBasicVariables: size doesn't match"
            );
        }
        basic_variables_ = basic_v;
    }

    void Tableau::overrideVariableNames(const std::map<int, std::string>& v_names)
    {
        if (v_names.size() != column_number_)
        {
            throw std::invalid_argument(
                "overrideVariableNames: size doesn't match"
            );
        }
        variable_names_ = v_names;
    }

    void Tableau::overrideArtificialVariables(const std::vector<int>& artificial_variables)
    {
        if (artificial_variables.size() >= row_number_-1)
        {
            throw std::invalid_argument(
                "overrideArtificialVariables: BigM vars cannot be more than constraint rows"
            );
        }
        this->artificial_variables_ = artificial_variables;
    }

    int Tableau::getIthRowIndex(const int rowIndex) const
    {
        return (rowIndex + 1) * column_number_;
    };

    int Tableau::executePivotStep()
    {
        // Find the variable with higher cost (column identification)
        auto it = std::min_element(
            tableau_buffer_.begin(),
            tableau_buffer_.begin() + column_number_ - 1
        );
        colIdx = std::distance(tableau_buffer_.begin(), it);
        // Evaluate the lower Ratio bi/aij (row identification)
        getRowLowestRatio();
        if (minRatioRowIndex == -1)
        {
            return -1;
        }
        // basic Variable vector update
        // the basic variable that exit is the one associated with the row
        // chosen for pivoting
        basic_variables_[minRatioRowIndex-1] = colIdx;
        // normalize the row: rowi <-- rowi/aij
        if (minRatioRowIndex >= 0)
        {
            normalizePivotedRow();
        }
        // Remove the basic variable component from the other rows
        // Transform the Objective Function row
        // row_i ← row_i - factor * pivot_row
        gaussJordanEliminationStep();
        return 0;
    }

    int Tableau::getStrideIndex(const int rowIndex, const int columnIndex) const
    {
        if (columnIndex >= column_number_ or rowIndex >= row_number_)
        {
            throw std::invalid_argument(
                "getStrideIndex: Row index or Column index incompatible with the buffer"
            );
        }
        return rowIndex * column_number_ + columnIndex;
    }

    void Tableau::getRowLowestRatio()
    {
        int aij_stride_index = 0;
        minRatioRowIndex = 0;
        int bIndex = 0;
        double ratio = 0.0;
        // this is used to track if unbound
        minRatio = -1.0;
        // loop for every constraint-row
        // skip first row because objective function
        for (int i = 1; i < row_number_; i++)
        {
            // retrieve aij index of the buffer
            aij_stride_index = getStrideIndex(i, colIdx);
            // check if aij is positive
            if (tableau_buffer_[aij_stride_index] > 0)
            {
                bIndex = getStrideIndex(i, column_number_-1);
                ratio = tableau_buffer_[bIndex] / tableau_buffer_[aij_stride_index];
                // check if ratio is lower and save index
                if (minRatio == -1.0)
                {
                    minRatio = ratio;
                    minRatioRowIndex = i;
                }
                else if (ratio < minRatio)
                {
                    minRatio = ratio;
                    minRatioRowIndex = i;
                }
            }
        }
        // loop finished, check if valid row was found, else unbounded
        if (minRatio == -1.0)
        {
            minRatioRowIndex = -1;
        }
    }


    void Tableau::normalizePivotedRow()
    {
        int gp_index;
        // normalize the row: rowi <-- rowi/aij
        auto a_ij = tableau_buffer_[getStrideIndex(minRatioRowIndex, colIdx)];
        for (int col_idx = 0; col_idx < column_number_ ; ++col_idx)
        {
            gp_index = getStrideIndex(minRatioRowIndex, col_idx);
            tableau_buffer_[gp_index] /= a_ij;
        }
    }

    void Tableau::gaussJordanEliminationStep()
    {
        // row_i ← row_i - factor * pivot_row
        int gp_index = 0;
        auto jg_buffer_start_index = getStrideIndex(minRatioRowIndex, 0);
        double mul_factor = 0.0;
        double decr_factor = 0.0;
        for (int row_idx = 0; row_idx < row_number_ ; ++row_idx)
        {
            mul_factor = tableau_buffer_[getStrideIndex(row_idx, colIdx)];
            for (int col_idx = 0; col_idx < column_number_ ; ++col_idx)
            {
                if (row_idx != minRatioRowIndex)
                {
                    decr_factor = mul_factor * tableau_buffer_[jg_buffer_start_index + col_idx];
                    gp_index = getStrideIndex(row_idx, col_idx);
                    tableau_buffer_[gp_index] -= decr_factor;
                }
            }
        }
    }

    int Tableau::objectiveFunctionTest() const
    {
        // exclude p and const from the search
        auto it = std::min_element(
            tableau_buffer_.begin(),
            tableau_buffer_.begin() + column_number_ - 2
        );
        if (*it < 0)
        {
            return -1;
        }
        return 0;
    }

    double Tableau::getRHS(const int basicVarIndex) const
    {
        bool is_basic = std::find(
            basic_variables_.begin(),
            basic_variables_.end(),
            basicVarIndex) != basic_variables_.end();
        if (!is_basic)
        {
            throw std::invalid_argument(
                "getRHS: Basic variable not present in the vector"
            );
        }
        int gp_index = 0;
        // this assumes that the reached solution is optimal
        // then only basic variable is 1 in only one row
        for (int row_idx = 1; row_idx < row_number_; row_idx++)
        {
            gp_index = getStrideIndex(row_idx, basicVarIndex);
            if (tableau_buffer_[gp_index] == 1)
            {
                return tableau_buffer_[getStrideIndex(row_idx, column_number_-1)];
            }
        }
        // this should never be reached
        throw std::runtime_error(
            "getRHS: Basic variable found in basis vector but no unit row found"
        );
    }

    double Tableau::getObjectiveFuncCoefficient(int varIdx) const
    {
        if (varIdx > column_number_ - 2)
        {
            throw std::invalid_argument(
              "VarIdx should be lower than available columns"
            );
        }
        return tableau_buffer_[varIdx];
    }

}
