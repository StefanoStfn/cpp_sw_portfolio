"""
Main Core gathers together all the test case classes and run those sequentially
"""
import unittest
from test_math_operators import TestMathOperators
from test_string_print import TestStringPrint
from test_features import TestFeatures

class MainCore():
    """
    Main Class, centrilized test channel
    """
    def __init__(self):
        self.suite = unittest.TestSuite()
        self.test_classes: list = [
            TestMathOperators,
            TestStringPrint,
            TestFeatures
        ]

    def __call__(self):
        for test in self.test_classes:
            self.suite.addTest(unittest.makeSuite(test))
        runner = unittest.TextTestRunner();
        runner.run(self.suite)

    