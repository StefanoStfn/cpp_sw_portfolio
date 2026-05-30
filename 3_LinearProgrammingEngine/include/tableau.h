//
// Created by Martina on 27/05/2026.
//

#ifndef INC_3_LINEARPROGRAMMINGENGINE_TABLEAU_H
#define INC_3_LINEARPROGRAMMINGENGINE_TABLEAU_H
#pragma once
#include <vector>

namespace LPEngine
{
    class Tableau
    {
        public:
            Tableau();
            void overrideBuffer(
                int row,
                int column,
                const std::vector<double> &buffer
            );
            void overrideBasicVariables(const std::vector<int> &var_v);
            int executePivotStep();
            int objectiveFunctionTest() const;
            const std::vector<int>& getBasicVariables() const {return basic_variables;};
            double getRHS(int basicVarIndex);
            double getObjFunctionRHS() const {return tableau_buffer_[column_number_-1];};
        private:
            std::vector<double> tableau_buffer_;
            int row_number_ = 0;
            int column_number_ = 0;
            // basic variable position
            std::vector<int> basic_variables;
            // utility methods
            int getIthRowIndex(int rowIndex) const;
            int getStrideIndex(int rowIndex, int columnIndex) const;
            void getRowLowestRatio();
            void normalizePivotedRow();
            void gaussJordanEliminationStep();
            std::vector<int> lowestRatioCheck;
            // pivot variables --> getRowLowestRatio function reset those
            int colIdx = 0;
            int aij_stride_index = 0;
            int minRatioRowIndex = 0;
            int bIndex = 0;
            double ratio = 0.0;
            double minRatio = -1.0;
            //pivot variables --> getRowLowestRatio function reset those
            int gp_index;
    };
}


#endif //INC_3_LINEARPROGRAMMINGENGINE_TABLEAU_H
