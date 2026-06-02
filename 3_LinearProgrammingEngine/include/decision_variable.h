//
// Created by Martina on 01/06/2026.
//

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
