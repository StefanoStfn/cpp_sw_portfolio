/**
* Public LPSolver API declaration.
*
* This class is the main frontend entry point for building and solving
* linear programming problems. It stores modeling-layer objects, exposes
* variable/constraint/objective registration methods, controls compilation
* and execution, and provides access to final solution status, objective
* value, variable values, degeneracy, and alternative-solution flags. The
* class also exposes debug accessors for inspecting the compiled simplex
* representation before running the backend.
*/

#ifndef INC_3_LINEARPROGRAMMINGENGINE_LP_SOLVER_H
#define INC_3_LINEARPROGRAMMINGENGINE_LP_SOLVER_H

#pragma once
#include <vector>
#include <map>
#include <optional>
#include "common/enums.h"
#include "modeling/decision_variable.h"
#include "modeling/relation_exp_wrapper.h"
#include "simplex/simplex_maincore.h"
#include "simplex/tableau_builder.h"

namespace LPEngine
{
    inline std::string version() {return "1.0.0";};

    class LPSolver
    {
        public:
            // API TO EXPOSE
            explicit LPSolver(
                SolverStrategy strategy = SolverStrategy::Simplex,
                SimplexStrategy solver_strategy = SimplexStrategy::BlandRule,
                double epsilon = 1E-9,
                double bigM = 1E6,
                int max_iterations = 4000
            );
            DecisionVariable& addVariable(const std::string& var_name);
            void addConstraint(const RelationExpression& constraint);
            void addObjectiveFunction(
                const RelationExpression& objective,
                OptimizationType opt_type
            );
            void addObjectiveFunction(
                const DecisionVariable& objective,
                OptimizationType opt_type
            );
            void run();
            SolveStatus getStatus() const { return status_;}
            double getOptimaSolutionRHS() const;
            std::map<std::string,double> getVariableValues();
            bool isDegenerateSolution() const {return degeneracy_;}
            bool isAlternativeSolution() const {return alternative_sol_;}
            // Debug window
            void compileSolver();
            void runSolver();
            std::map<std::string, int> getColumnNameMap() const {return column_name_map_;}
            RelationExpression getObjective() const {return objective_;}
            RelationExpression getRowConstraint(int index) const {return constraints_.at(index);}
            std::vector<int> getBasicVariables() const {return basic_variables_;}
        private:
            // common
            double epsilon_;
            double bigM_;
            int max_iterations_;
            SolverStrategy strategy_;
            SimplexStrategy solver_strategy_;
            std::vector<RelationExpression> constraints_;
            RelationExpression objective_;
            OptimizationType opt_type_ = OptimizationType::Maximize;
            std::vector<DecisionVariable> decision_variables_;
            std::map<std::string, int> column_name_map_;
            std::vector<std::string> var_order_;
            int col_id_counter = 0;
            // Simplex Tableau Variables
            std::optional<TableauBuilder> t_builder_;
            std::vector<double> buffer_;
            std::vector<int> basic_variables_;
            std::optional<SimplexMainCore> simplex_maincore_;
            std::vector<int> artificial_variables_;
            // Common
            SolveStatus status_ = SolveStatus::NotStarted;
            bool degeneracy_ = false;
            bool alternative_sol_ = false;
            void sanityCheck();
            // Simplex Specific Methods
            void runSimplexBuilding();
            int getDecisionVariableCount() const {return decision_variables_.size();}
            void defineRepresentationOrder(int ss_num, int c_init_size, int av_num);
            void buildBasicVarVect();
            void standardizeSigns();
            void buildBuffer();
            void buildRunSimplexSolver(int row_num, int col_num);
            // InteriorPoint Variables and Methods
            void runInteriorPointBuilding();
    };
}


#endif //INC_3_LINEARPROGRAMMINGENGINE_LP_SOLVER_H
