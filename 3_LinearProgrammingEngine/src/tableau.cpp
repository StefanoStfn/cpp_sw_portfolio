//
// Created by Martina on 27/05/2026.
//

#include "../include/tableau.h"

#include <stdexcept>

namespace LPEngine {
    Tableau::Tableau()
    {
        //ctor
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

    int Tableau::getIthRowIndex(const int rowIndex) const
    {
        return (rowIndex + 1) * column_number_;
    };

    void Tableau::executePivotStep()
    {

    }

}
