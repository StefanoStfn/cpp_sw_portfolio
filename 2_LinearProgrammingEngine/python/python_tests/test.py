# tests/test_python_interface.py

import unittest

import lpengine as lp


class TestPythonInterface(unittest.TestCase):

    def test_classic_feasible_problem(self):
        solver = lp.LPSolver()
        x = solver.add_variable("x")
        y = solver.add_variable("y")
        solver.add_constraint(2*x + y <= 10)
        solver.add_constraint(x + y <= 7)
        solver.add_constraint(x + 2*y <= 12)
        solver.objective_function(30*x + 40*y, lp.Maximize)
        solver.run()
        values = solver.get_variable_values()
        self.assertEqual(solver.get_status(), lp.Optimal)
        self.assertAlmostEqual(solver.get_solution_rhs(), 260.0, places=9)
        self.assertAlmostEqual(values["x"], 2.0, places=9)
        self.assertAlmostEqual(values["y"], 5.0, places=9)

    def test_minimize_big_m_problem(self):
        solver = lp.LPSolver(epsilon=1e-9)
        x = solver.add_variable("x")
        y = solver.add_variable("y")
        solver.add_constraint(x + y >= 10)
        solver.add_constraint(x <= 8)
        solver.add_constraint(y <= 8)
        solver.objective_function(3*x + 2*y, lp.Minimize)
        solver.run()
        values = solver.get_variable_values()
        self.assertEqual(solver.get_status(), lp.Optimal)
        self.assertAlmostEqual(solver.get_solution_rhs(), 22.0, places=9)
        self.assertAlmostEqual(values["x"], 2.0, places=9)
        self.assertAlmostEqual(values["y"], 8.0, places=9)
        self.assertAlmostEqual(values["a0"], 0.0, places=9)

    def test_unbounded_problem(self):
        solver = lp.LPSolver()
        x = solver.add_variable("x")
        y = solver.add_variable("y")
        solver.add_constraint(x - y <= 1)
        solver.objective_function(x + y, lp.Maximize)
        solver.run()
        self.assertEqual(solver.get_status(), lp.Unbounded)

    def test_infeasible_problem(self):
        solver = lp.LPSolver()
        x = solver.add_variable("x")
        y = solver.add_variable("y")
        solver.add_constraint(x + y >= 10)
        solver.add_constraint(x + y <= 5)
        solver.objective_function(x + y, lp.Maximize)
        solver.run()
        self.assertEqual(solver.get_status(), lp.Infeasible)
        values = solver.get_variable_values()
        self.assertAlmostEqual(values["a0"], 5.0, places=9)

if __name__ == "__main__":
    unittest.main()