/**
* Tableau construction layer for simplex-compatible LP models.
*
* This class converts compiled frontend expressions into a canonical tableau
* structure. It receives constraints, objective metadata, optimization type,
* and decision variables; then computes row/column dimensions, inserts
* slack, surplus, and artificial variables, completes missing coefficient
* columns, and applies Big-M objective canonicalization. The resulting
* constraints and objective are consumed by LPSolver to build the flattened
* tableau buffer and initial simplex basis.
*/

#ifndef INC_3_LINEARPROGRAMMINGENGINE_TABLEAU_BUILDER_H
#define INC_3_LINEARPROGRAMMINGENGINE_TABLEAU_BUILDER_H

#pragma once
#include <vector>
#include "modeling/relation_exp_wrapper.h"
#include "common/enums.h"

namespace LPEngine
{
    class TableauBuilder
    {
        public:
            TableauBuilder(
                const std::vector<RelationExpression>& constraints,
                const RelationExpression& obj_function,
                const OptimizationType& optimization_type,
                int decision_variable_count,
                const std::vector<DecisionVariable>& decision_variables
            );
            void buildTableau();
            int getSSNumber() const {return ss_var_num_;}
            int getAVNumber() const {return av_var_num_;}
            int getRowNumber() const {return row_number_;}
            int getColNumber() const {return column_number_;}
            std::vector<RelationExpression> getConstraints() const {return constraints_;}
            RelationExpression getObjective() const {return obj_function_;}

        private:
            std::vector<double> buffer_;
            std::vector<RelationExpression> constraints_;
            std::vector<std::string> decision_var_names_;
            RelationExpression obj_function_;
            OptimizationType optimization_type_;
            int row_number_;
            int column_number_ = 0;
            int ss_var_num_ = 0;
            int av_var_num_ = 0;
            void moveObjectiveComponentLHS();
            void insertSlackSurplusArtVarObjFactor();
            void completeSlackSurplusColumns();
            void completeDecisionVariableColumns();
            void canonicalizeObjectiveFunction();
    };
}


#endif //INC_3_LINEARPROGRAMMINGENGINE_TABLEAU_BUILDER_H
