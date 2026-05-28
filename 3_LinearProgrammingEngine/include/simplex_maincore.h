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
            SimplexMainCore();
            //void addConstraint();
            //void addObjectiveFunction();
            void feasibleMockStartup();
            void artificialVarMockStartup();
            void unboundedMockStartup();
            void unfeasibleMockStartup();
            void degeneracyMockStartup();
            void alternativeOptSolMockStartup();
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
            // Tableau
            std::optional<Tableau> tableau_;
            // Methods
            void executePivotStep();
            void checkTermination();
            void executeReading();
    };
}


#endif //INC_3_LINEARPROGRAMMINGENGINE_SIMPLEX_MAINCORE_H
