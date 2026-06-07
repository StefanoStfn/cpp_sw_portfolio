/**
* Decision variable implementation.
*
* This file defines the lightweight constructor for DecisionVariable,
* storing the symbolic variable name and its internal column identifier.
* The object is used by the modeling frontend to build algebraic LP expressions.
*/

#include "modeling/decision_variable.h"


namespace LPEngine
{
    DecisionVariable::DecisionVariable(
        const std::string& name,
        int col_id
        )
    {
        this->name_ = name;
        this->col_id_ = col_id;
    }

}