/**
* Decision variable model declaration.
*
* This class represents a user-defined LP decision variable in the modeling
* frontend. Each variable stores its symbolic name and internal column id,
* allowing algebraic expressions to be mapped later into tableau columns.
* Decision variables are created through LPSolver and then combined with
* operators to build linear expressions, constraints, and objectives.
*/

#ifndef INC_3_LINEARPROGRAMMINGENGINE_DECISION_VARIABLE_H
#define INC_3_LINEARPROGRAMMINGENGINE_DECISION_VARIABLE_H

#pragma once
#include <string>
#include <vector>

namespace LPEngine
{

    class DecisionVariable
    {
        public:
            explicit DecisionVariable(
                const std::string& name,
                int col_id
            );
            std::string getName() const {return name_;}

        private:
            std::string name_;
            int col_id_;
    };
}

#endif //INC_3_LINEARPROGRAMMINGENGINE_DECISION_VARIABLE_H
