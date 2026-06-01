/**
* Main orchestration class for the simplex-based LP engine.
*
* SimplexMainCore owns the solver state machine and coordinates the execution
* flow from tableau availability through Phase II pivoting, termination checks,
* iteration-limit handling, and final solution reading. The class stores the
* final solve status, objective value access, variable-value extraction, and
* solution-level flags such as degeneracy and alternative optima. It operates
* on an already-created Tableau object; LP standardization, model parsing, and
* tableau construction are treated as separate layers.
*/


#ifndef INC_3_LINEARPROGRAMMINGENGINE_SIMPLEX_MAINCORE_H
#define INC_3_LINEARPROGRAMMINGENGINE_SIMPLEX_MAINCORE_H
#pragma once
#include <optional>
#include "tableau.h"

namespace LPEngine
{
    class SimplexMainCore
    {
        public:
            explicit SimplexMainCore(
                double epsilon = 1E-6,
                double bigM = 1E6,
                int max_iterations = 4000,
                SimplexStrategy solver_strategy = SimplexStrategy::BlandRule
            );
            explicit SimplexMainCore(
                Tableau& tableau,
                double epsilon = 1E-6,
                double bigM = 1E6,
                int max_iterations = 4000,
                SimplexStrategy solver_strategy = SimplexStrategy::BlandRule
            );
            // Status Encoding
            enum class SolveStatus {
                NotStarted,
                Optimal,
                Infeasible,
                Unbounded,
                IterationLimitReached
            };
            // Utility methods
            void resetEngine();
            void startEngine();
            // API TO EXPOSE
            SolveStatus getStatus() const { return status_;}
            double getOptimaSolutionRHS() const;
            std::map<std::string,double> getVariableValues();
            bool isDegenerateSolution() const {return degeneracy_;}
            bool isAlternativeSolution() const {return alternative_sol_;}
        private:
            // Variables
            SimplexStrategy solver_strategy_;
            //  State Machine
            enum class EngineState_
            {
                Reset,
                Standardization,
                CheckFeasibility,
                TableauCreation,
                PhaseI,
                PhaseII,
                TerminationCheck,
                Reading,
                IterationLimit,
            };
            EngineState_ present_state_ = EngineState_::PhaseII;
            EngineState_ next_state_ = EngineState_::PhaseII;
            bool loopCondition_ = true;
            double epsilon;
            bool degeneracy_ = false;
            bool alternative_sol_ = false;
            double bigM;
            int max_iterations_;
            int iteration_count_ = 0;
            // Tableau
            std::optional<Tableau> tableau_;
            int pivotResult = 0;
            SolveStatus status_ = SolveStatus::NotStarted;
            // Methods
            void executePivotStep();
            void checkTermination();
            void executeReading();
            void printFeasibleSolution(std::vector<int>& basic_variables);
            void printReading(std::vector<int>& basic_variables);
            bool artificialVariableCheck() const;
            void alternativeSolutionsCheck(std::vector<int>& basic_variables);
            void reportIterationLimit();
    };
}


#endif //INC_3_LINEARPROGRAMMINGENGINE_SIMPLEX_MAINCORE_H
