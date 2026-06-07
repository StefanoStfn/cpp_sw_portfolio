from typing import Dict
from enum import Enum

# Enums definition
class OptimizationType(Enum):
    """Optimization direction for the LP objective."""
    Maximize: "OptimizationType"
    Minimize: "OptimizationType"

class SolverStrategy(Enum):
    """The Solver Strategy to be used by the Engine"""
    Simplex: "SolverStrategy"

class SimplexStrategy(Enum):
    """Which methodology the Simplex should use."""
    MostNegative: "SimplexStrategy"
    BlandRule: "SimplexStrategy"

class SolveStatus(Enum):
    """The status label for the solver results"""
    NotStarted: "SolveStatus"
    Optimal: "SolveStatus"
    Infeasible: "SolveStatus"
    Unbounded: "SolveStatus"
    IterationLimitReached: "SolveStatus"

# OptimizationType
Maximize: OptimizationType
Minimize: OptimizationType
# SolverStrategy
Simplex: SolverStrategy
# Simplex Strategy
MostNegative: SimplexStrategy
BlandRule: SimplexStrategy
# SolveStatus
NotStarted: SolveStatus
Optimal: SolveStatus
Infeasible: SolveStatus
Unbounded: SolveStatus
IterationLimitReached: SolveStatus


class LPSolver:
    """
    Linear programming solver api frontend.

    This class exposes the Python API for building and solving continuous
    linear programming problems.
    """

    def __init__(
        self,
        strategy: SolverStrategy = Simplex,
        solver_strategy: SimplexStrategy = BlandRule,
        epsilon: float = 1e-9,
        bigM: float = 1e6,
        max_iterations: int = 4000,
    ) -> None:
        """
        Create an LP solver instance.

        Parameters
        ----------
        strategy : SolverStrategy, default=Simplex
            Backend algorithm used to solve the LP problem.
        solver_strategy : SimplexStrategy, default=BlandRule
            Pivot-selection strategy used by the simplex backend.
        epsilon : float, default=1e-9
            Numerical tolerance used for floating-point comparisons.
        bigM : float, default=1e6
            Big-M penalty value used for artificial variables.
        max_iterations : int, default=4000
            Maximum number of simplex iterations before stopping.
        """
        ...

    def add_variable(self, var_name: str) -> DecisionVariable:
        """
        Add a decision variable to the LP model.

        Parameters
        ----------
        var_name : str
            Unique symbolic name of the decision variable.

        Returns
        -------
        DecisionVariable
            Variable object used to build constraints and objectives.
        """
        ...

    def add_constraint(self, constraint: RelationExpression) -> None:
        """
        Add a constraint to the LP model.

        Parameters
        ----------
        constraint : RelationExpression
            Constraint expression created with '<=', '>=', or '=='.
        """
        ...

    def objective_function(
        self,
        objective: RelationExpression | DecisionVariable,
        opt_type: OptimizationType,
    ) -> None:
        """
        Add the objective function.

        Parameters
        ----------
        objective : RelationExpression or DecisionVariable
            Linear objective expression.
        opt_type : OptimizationType
            Optimization direction, either 'Maximize' or 'Minimize'.
        """
        ...

    def run(self) -> None:
        """
        Compile and solve the LP problem.
        """
        ...

    def get_status(self) -> SolveStatus:
        """
        Return the final solver status.

        Returns
        -------
        SolveStatus
            Status of the solved problem.
        """
        ...

    def get_solution_rhs(self) -> float:
        """
        Return the optimal objective value.

        Returns
        -------
        float
            Objective value of the final solution.
        """
        ...

    def get_variable_values(self) -> Dict[str, float]:
        """
        Return the final variable values.

        Returns
        -------
        dict[str, float]
            Mapping from variable name to solved value.
        """
        ...

    def is_degenerate(self) -> bool:
        """
        Return whether the final solution is degenerate.

        Returns
        -------
        bool
            'True' if the solution is degenerate.
        """
        ...

    def is_alternative_sol(self) -> bool:
        """
        Return whether multiple optimal solutions exist.

        Returns
        -------
        bool
            'True' if the problem has alternative optimal solutions.
        """
        ...