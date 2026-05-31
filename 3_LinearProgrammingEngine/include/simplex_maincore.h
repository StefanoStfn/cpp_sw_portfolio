//
//
//

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
                double bigM = 1E6
            );
            explicit SimplexMainCore(
                Tableau& tableau,
                double epsilon = 1E-6,
                double bigM = 1E6
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
            void feasibleMockStartup();
            void unboundedMockStartup();
            void unfeasibleMockStartup();
            void degeneracyMockStartup();
            void alternativeOptSolMockStartup();
            void resetEngine();
            void startEngine();
            // public API exposed to Python Bindings
            SolveStatus getStatus() const { return status_;}
            double getOptimaSolutionRHS() const;
            std::map<std::string,double> getVariableValues();
            bool hasDegenerateSolution() const {return degeneracy_;}
            bool hasAlternativeSolution() const {return alternative_sol_;}
        private:
            // Variables
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
                Reading
            };
            EngineState_ present_state_ = EngineState_::PhaseII;
            EngineState_ next_state_ = EngineState_::PhaseII;
            bool loopCondition_ = true;
            double epsilon;
            bool degeneracy_ = false;
            bool alternative_sol_ = false;
            double bigM;
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
    };
}


#endif //INC_3_LINEARPROGRAMMINGENGINE_SIMPLEX_MAINCORE_H
