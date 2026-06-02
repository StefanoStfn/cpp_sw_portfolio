//
// Created by Martina on 01/06/2026.
//

#include "../include/decision_variable.h"


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