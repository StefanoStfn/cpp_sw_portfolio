//
// Created by Martina on 27/05/2026.
//

#ifndef INC_3_LINEARPROGRAMMINGENGINE_TABLEAU_H
#define INC_3_LINEARPROGRAMMINGENGINE_TABLEAU_H
#pragma once
#include <vector>
#include <string>
#include <map>
#include <stdexcept>
#include <iostream>
#include <algorithm>

namespace LPEngine
{
    class Tableau
    {
        public:
            Tableau();
            void reset();
            void overrideBuffer(
                int row,
                int column,
                const std::vector<double> &buffer
            );
            void overrideBasicVariables(const std::vector<int> &basic_v);
            void overrideVariableNames(const std::map<int, std::string>& v_names);
            void overrideArtificialVariables(const std::vector<int>& artificial_variables);
            int executePivotStep();
            int objectiveFunctionTest() const;
            const std::vector<int>& getBasicVariables() const {return basic_variables;};
            double getRHS(int basicVarIndex);
            double getObjFunctionRHS() const {return tableau_buffer_[column_number_-1];};
            int getColIdx() const {return colIdx; };
            std::string getVarName(int varIdx) {return variable_names_.at(varIdx);};
            int getColNum() const {return column_number_;};
            std::vector<int> getArtificialVariables() const {return artificial_variables_;};
        private:
            std::vector<int> artificial_variables_;
            std::vector<double> tableau_buffer_;
            int row_number_ = 0;
            int column_number_ = 0;
            // basic variable position
            std::vector<int> basic_variables;
            std::map<int, std::string> variable_names_;
            // pivot variables
            std::vector<int> lowestRatioCheck;
            int colIdx = 0;
            int aij_stride_index = 0;
            int minRatioRowIndex = 0;
            int bIndex = 0;
            double ratio = 0.0;
            double minRatio = -1.0;
            int gp_index = 0;
            // utility methods
            int getIthRowIndex(int rowIndex) const;
            int getStrideIndex(int rowIndex, int columnIndex) const;
            void getRowLowestRatio();
            void normalizePivotedRow();
            void gaussJordanEliminationStep();
    };
}


#endif //INC_3_LINEARPROGRAMMINGENGINE_TABLEAU_H
