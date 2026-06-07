/**
 * Binding Interface for Solver Library
 */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include "interface/lp_solver.h"

namespace py = pybind11;


PYBIND11_MODULE(lpengine, m, py::mod_gil_not_used())
{
    m.doc() = "Linear Programming Engine developed by Stefano Pala";
    m.def(
        "version",
        &LPEngine::version,
        "The Library Version");
    // Enum Types
    py::enum_<LPEngine::OptimizationType>(m, "OptimizationType")
        .value("Maximize", LPEngine::OptimizationType::Maximize)
        .value("Minimize", LPEngine::OptimizationType::Minimize);
    m.attr("Maximize") = LPEngine::OptimizationType::Maximize;
    m.attr("Minimize") = LPEngine::OptimizationType::Minimize;
    // Solver Strategy
    py::enum_<LPEngine::SolverStrategy>(m, "SolverStrategy")
        .value("Simplex", LPEngine::SolverStrategy::Simplex);
    m.attr("Simplex") = LPEngine::SolverStrategy::Simplex;
    // Simplex Strategy
    py::enum_<LPEngine::SimplexStrategy>(m, "SimplexStrategy")
        .value("MostNegative", LPEngine::SimplexStrategy::MostNegative)
        .value("BlandRule", LPEngine::SimplexStrategy::BlandRule);
    m.attr("MostNegative") = LPEngine::SimplexStrategy::MostNegative;
    m.attr("BlandRule") = LPEngine::SimplexStrategy::BlandRule;
    // Solver Status
    py::enum_<LPEngine::SolveStatus>(m, "SolveStatus")
        .value("NotStarted", LPEngine::SolveStatus::NotStarted)
        .value("Optimal", LPEngine::SolveStatus::Optimal)
        .value("Infeasible", LPEngine::SolveStatus::Infeasible)
        .value("Unbounded", LPEngine::SolveStatus::Unbounded)
        .value("IterationLimitReached", LPEngine::SolveStatus::IterationLimitReached);
    m.attr("NotStarted") = LPEngine::SolveStatus::NotStarted;
    m.attr("Optimal") = LPEngine::SolveStatus::Optimal;
    m.attr("Infeasible") = LPEngine::SolveStatus::Infeasible;
    m.attr("Unbounded") = LPEngine::SolveStatus::Unbounded;
    m.attr("IterationLimitReached") = LPEngine::SolveStatus::IterationLimitReached;

    // Decision Variable Operators
    py::class_<LPEngine::DecisionVariable>(m, "DecisionVariable")
        .def("get_name", &LPEngine::DecisionVariable::getName)
        .def("__rmul__", [](const LPEngine::DecisionVariable& v, double c) {
            return c * v;})
        .def("__mul__", [](const LPEngine::DecisionVariable& v, double c) {
            return v * c;})
        .def("__neg__", [](const LPEngine::DecisionVariable& v) {
            return -v;})
        .def("__add__", [](
            const LPEngine::DecisionVariable& v,
            const LPEngine::DecisionVariable& c) {
            return v + c;})
        .def("__add__", [](
            const LPEngine::DecisionVariable& v,
            const LPEngine::RelationExpression& c) {
            return v + c;})
        .def("__sub__", [](
            const LPEngine::DecisionVariable& v,
            const LPEngine::DecisionVariable& c) {
            return v - c;})
        .def("__sub__", [](
            const LPEngine::DecisionVariable& v,
            const LPEngine::RelationExpression& c) {
            return v - c;})
        .def("__le__", [](const LPEngine::DecisionVariable& v, double rhs) {
            return v <= rhs;})
        .def("__ge__", [](const LPEngine::DecisionVariable& v, double rhs) {
            return v >= rhs;})
        .def("__eq__", [](const LPEngine::DecisionVariable& v, double rhs) {
            return v == rhs;});
    // Relation Expression Operators
    py::class_<LPEngine::RelationExpression>(m, "RelationExpression")
        .def("str", &LPEngine::RelationExpression::toString)
        .def("str_table", &LPEngine::RelationExpression::toStringTable)
        .def("__rmul__", [](const LPEngine::RelationExpression& v, double c) {
            return c * v;})
        .def("__mul__", [](const LPEngine::RelationExpression& v, double c) {
            return v * c; })
        .def("__neg__", [](const LPEngine::RelationExpression& v) {
            return -v;})
        .def("__add__", [](
            const LPEngine::RelationExpression& v,
            const LPEngine::DecisionVariable& c) {
            return v + c;})
        .def("__add__", [](
            const LPEngine::RelationExpression& v,
            const LPEngine::RelationExpression& c) {
            return v + c;})
        .def("__sub__", [](
            const LPEngine::RelationExpression& v,
            const LPEngine::DecisionVariable& c) {
            return v - c;})
        .def("__sub__", [](
            const LPEngine::RelationExpression& v,
            const LPEngine::RelationExpression& c) {
            return v - c;})
        .def("__le__", [](const LPEngine::RelationExpression& v, double rhs) {
            return v <= rhs;})
        .def("__ge__", [](const LPEngine::RelationExpression& v, double rhs) {
            return v >= rhs; })
        .def("__eq__", [](const LPEngine::RelationExpression& v, double rhs) {
            return v == rhs;});

    // Solver API
    py::class_<LPEngine::LPSolver>(m, "LPSolver")
    .def(
        py::init<
            LPEngine::SolverStrategy, LPEngine::SimplexStrategy,
            double, double, int>(),
            py::arg("strategy") = LPEngine::SolverStrategy::Simplex,
            py::arg("solver_strategy") = LPEngine::SimplexStrategy::BlandRule,
            py::arg("epsilon") = 1E-9,
            py::arg("bigM") = 1E6,
            py::arg("max_iterations") = 4000)
    .def("add_variable",
        &LPEngine::LPSolver::addVariable,
        py::return_value_policy::copy,
        "Add decision Variable Identifier",
        py::arg("var_name"))
    .def("add_constraint",
        &LPEngine::LPSolver::addConstraint,
        "Add Constraint expression to the problem",
        py::arg("constraint"))
    .def("objective_function",
        py::overload_cast<
            const LPEngine::RelationExpression&,
            LPEngine::OptimizationType>(&LPEngine::LPSolver::addObjectiveFunction),
        "Add the objective function to minimize or maximize",
        py::arg("objective"),
        py::arg("opt_type"))
    .def("objective_function",
        py::overload_cast<
            const LPEngine::DecisionVariable&,
            LPEngine::OptimizationType>(&LPEngine::LPSolver::addObjectiveFunction),
        "Add the objective function to minimize or maximize",
        py::arg("objective"),
        py::arg("opt_type"))
    .def("get_variable_values",
        &LPEngine::LPSolver::getVariableValues,
        "Return the variables result of the problem")
    .def("run",
        &LPEngine::LPSolver::run,
        "Run the optimization engine")
    .def("get_status",
        &LPEngine::LPSolver::getStatus,
        "Get the problem status")
    .def("get_solution_rhs",
        &LPEngine::LPSolver::getOptimaSolutionRHS,
        "Get the RHS result of the problem")
    .def("is_degenerate",
        &LPEngine::LPSolver::isDegenerateSolution,
        "Flag if the Problem has degenerate solutions")
    .def("is_alternative_sol",
        &LPEngine::LPSolver::isAlternativeSolution,
        "Flag if the problem has multiple optimal solutions");
}
