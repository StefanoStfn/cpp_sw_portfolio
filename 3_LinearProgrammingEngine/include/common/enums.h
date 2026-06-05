/**
* Shared solver constants and enum definitions.
*
* This header defines symbolic keys used by the tableau representation,
* default numerical constants, and the enum types shared across the engine.
* The enums describe constraint senses, solver backend selection,
* optimization direction, simplex pivot strategy, and final solve status.
* These definitions are used by the modeling layer, frontend solver API,
* tableau builder, simplex core, and result reporting logic.
*/

#ifndef INC_3_LINEARPROGRAMMINGENGINE_ENUMS_H
#define INC_3_LINEARPROGRAMMINGENGINE_ENUMS_H

#pragma once

#define RHS_KEY "RHS"
#define OBJ_PROB "OBJ_VAR"
#define BIG_M 1E6
#define EPS 1E-9

namespace LPEngine
{
    // For Relation Expressions operators
    enum class ConstraintSense
    {
        Reset,
        Equal,
        GreaterEqual,
        LessEqual
    };
    // Which Algorithm should be used for solving the LP
    enum class SolverStrategy
    {
        Simplex,
        InteriorPoint
    };
    // the Optimization problem to be solved
    enum class OptimizationType
    {
        Maximize,
        Minimize
    };
    // Pivot Strategy
    enum class SimplexStrategy
    {
        MostNegative,
        BlandRule
    };
    // Status Encoding
    enum class SolveStatus {
        NotStarted,
        Optimal,
        Infeasible,
        Unbounded,
        IterationLimitReached
    };
}
#endif //INC_3_LINEARPROGRAMMINGENGINE_ENUMS_H
