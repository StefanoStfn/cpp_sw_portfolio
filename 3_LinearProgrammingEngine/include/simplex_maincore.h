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
            SimplexMainCore(double epsilon = 1E-6, double bigM = 1E6);
            //void addConstraint();
            //void addObjectiveFunction();
            void feasibleMockStartup();
            void artificialVarMockStartup();
            void unboundedMockStartup();
            void unfeasibleMockStartup();
            void degeneracyMockStartup();
            void alternativeOptSolMockStartup();
            void resetEngine();
            void startEngine();
        private:
            // Variables
            //  State Machine
            enum class State_
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
            State_ present_state_ = State_::PhaseII;
            State_ next_state_ = State_::PhaseII;
            bool loopCondition_ = true;
            double epsilon;
            bool degeneracy_ = false;
            double bigM;
            // Tableau
            std::optional<Tableau> tableau_;
            int pivotResult = 0;
            // Methods
            void executePivotStep();
            void checkTermination();
            void executeReading();
            void printFeasibleSolution(std::vector<int>& basic_variables);
            void printReading(std::vector<int>& basic_variables);
            bool artificialVariableCheck();
    };
}


#endif //INC_3_LINEARPROGRAMMINGENGINE_SIMPLEX_MAINCORE_H
