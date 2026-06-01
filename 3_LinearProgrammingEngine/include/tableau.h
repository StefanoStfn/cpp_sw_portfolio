/**
* Tableau representation and pivot engine for the simplex solver.
*
* The Tableau class owns the flattened row-major simplex tableau, basis
* metadata, variable-name mapping, artificial-variable tracking, and pivot
* strategy configuration. It provides the low-level operations required by
* the simplex core: objective-row inspection, entering/leaving variable
* selection, ratio testing, Gauss-Jordan pivot execution, basis updates, and
* RHS/objective-value access. This class does not build an LP from user input;
* it assumes the tableau has already been constructed by an external layer.
*/

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
    // Pivot Strategy
    enum class SimplexStrategy
    {
        MostNegative,
        BlandRule
    };

    class Tableau
    {
        public:
            explicit Tableau(
                SimplexStrategy solver_strategy = SimplexStrategy::BlandRule,
                double epsilon = 1E-12
            );
            void reset();
            void setBuffer(
                int row,
                int column,
                const std::vector<double> &buffer
            );
            void setBasicVariables(const std::vector<int> &basic_v);
            void setVariableNames(const std::map<int, std::string>& v_names);
            void setArtificialVariables(const std::vector<int>& artificial_variables);
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
            // Pivot Strategy
            SimplexStrategy solver_strategy_;
            double epsilon_;
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
