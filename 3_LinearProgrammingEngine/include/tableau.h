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
            const std::vector<int>& getBasicVariables() const {return basic_variables_;}
            double getRHS(int basicVarIndex) const;
            double getObjFunctionRHS() const {return tableau_buffer_[column_number_-1];}
            int getColIdx() const {return colIdx;}
            int getRowIdx() const {return minRatioRowIndex;}
            std::string getVarName(int varIdx) {return variable_names_.at(varIdx);}
            int getColNum() const {return column_number_;}
            std::vector<int> getArtificialVariables() const {return artificial_variables_;}
            double getObjectiveFuncCoefficient(int varIdx) const;
        private:
            // Tableau State Variables
            std::vector<int> basic_variables_;
            std::map<int, std::string> variable_names_;
            std::vector<int> artificial_variables_;
            std::vector<double> tableau_buffer_;
            int row_number_ = 0; // Tableau dimension description
            int column_number_ = 0; // Tableau dimension description
            // pivot variables
            int colIdx = 0; // Present Column State
            int minRatioRowIndex = 0; // Present Row State
            double minRatio = -1.0; // minimum Ratio State
            // utility methods
            int getIthRowIndex(int rowIndex) const;
            int getStrideIndex(int rowIndex, int columnIndex) const;
            void getRowLowestRatio();
            void normalizePivotedRow();
            void gaussJordanEliminationStep();
    };
}


#endif //INC_3_LINEARPROGRAMMINGENGINE_TABLEAU_H
