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
            void executePivotStep();
        private:
            std::vector<double> tableau_buffer_;
            int row_number_ = 0;
            int column_number_ = 0;
            // utility methods
            int getIthRowIndex(int rowIndex) const;
    };
}


#endif //INC_3_LINEARPROGRAMMINGENGINE_TABLEAU_H
