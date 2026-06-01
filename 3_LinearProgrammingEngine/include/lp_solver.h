//
// Created by Martina on 01/06/2026.
//

#ifndef INC_3_LINEARPROGRAMMINGENGINE_LP_SOLVER_H
#define INC_3_LINEARPROGRAMMINGENGINE_LP_SOLVER_H

#pragma once
#include "simplex_maincore.h"
#include "column_vector.h"

namespace LPEngine
{
    enum class SolverStrategy
    {
        Simplex,
        InteriorPoint
    };

    class LPSolver
    {
        public:
            explicit LPSolver(SolverStrategy strategy = SolverStrategy::Simplex);
            void addVariable(const std::string& var_name);
            void addConstraint();
            void addObjectiveFunction();
            void solve();
        private:
            void runSimplex();
            void runInteriorPoint();
            SolverStrategy strategy_;
            std::map<int, ColumnVector> column_vector_map_;
            std::map<std::string, int> column_name_map_;
            int col_id_counter = 0;
    };
}


#endif //INC_3_LINEARPROGRAMMINGENGINE_LP_SOLVER_H
