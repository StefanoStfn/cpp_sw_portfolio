/**
* Linear expression and constraint representation.
*
* This class stores the symbolic coefficient map used by the modeling layer
* and later consumed by the tableau builder. A RelationExpression can
* represent either a plain linear expression, an objective function, or a
* finalized constraint depending on its constraint sense and metadata. It
* also tracks generated slack/surplus/artificial variable indices, the
* initial basic variable name for each compiled row, and debug string
* serialization helpers for expression and tableau inspection.
*/

#ifndef INC_3_LINEARPROGRAMMINGENGINE_RELATION_EXPRESSION_H
#define INC_3_LINEARPROGRAMMINGENGINE_RELATION_EXPRESSION_H

#pragma once
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include "decision_variable.h"
#include "common/enums.h"


namespace LPEngine
{
    class RelationExpression
    {
        public:
            RelationExpression();
            explicit RelationExpression(const std::map<std::string, double> &coefficients);
            const std::map<std::string, double>& getCoefficients() const {return coefficients_;}
            void setConstraintSense(ConstraintSense constraint_sense);
            ConstraintSense getConstraintSense() const {return constraint_sense_;};
            std::string toString() const;
            std::string toStringTable() const;
            void setCoefficient(std::string c_name, double coefficient);
            void setSSIndex(int index) {ss_index_ = index;}
            int getSSIndex() const {return ss_index_;}
            void setAVIndex(int index) {av_index_ = index;}
            int getAVIndex() const {return av_index_;}
            std::string getBasicVarName() const {return b_var_name_;}
            void setBasicVarName(const std::string& b_var_name) { b_var_name_ = b_var_name;}
            bool getHasObjective() const {return has_objective_;}
            void setHasObjective() {has_objective_ = true;}

        private:
            std::map<std::string, double> coefficients_;
            ConstraintSense constraint_sense_ = ConstraintSense::Reset;
            int ss_index_ = -1;
            int av_index_ = -1;
            std::string b_var_name_;
            bool has_objective_ = false;
    };
}


#endif //INC_3_LINEARPROGRAMMINGENGINE_RELATION_EXPRESSION_H
