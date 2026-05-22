"""
Testing Sum, Difference, Multiplication and Division Operators

Array -> Array, 
Array -> Scalar, 
Scalar -> Array

"""
import unittest
import numtoy as nt

class TestMathOperators(unittest.TestCase):
    """
    Testing the mathematical operators
    """
    def setUp(self):
        """
        The 2 created Tensors have the same content
        """
        self.a_array = nt.NToyArray(shape=(4,2))
        self.b_array = nt.NToyArray(shape=(4,2))

    def test_scalar_plus_array(self):
        """
        Scalar + Array, check type and result
        """
        self.assertIsInstance(
            2.0 + self.a_array,
            nt.NToyArray
        )
        c_array = 2.0 + self.a_array
        self.assertEqual(
            c_array[0,0],
            2.0
        )

    def test_array_plus_scalar(self):
        """
        Array + Scalar, check type and result
        """
        self.assertIsInstance(
            self.a_array + 10.0,
            nt.NToyArray
        )
        c_array = self.a_array + 10.0
        self.assertEqual(
            c_array[3,1],
            17.0
        )

    def test_array_plus_array(self):
        """
        Array + Array, check type and result
        """
        self.assertIsInstance(
            self.a_array + self.b_array,
            nt.NToyArray
        )
        c_array = self.a_array + self.b_array
        self.assertEqual(
            c_array[3,1],
            14.0
        )

    def test_scalar_minus_array(self):
        """
        Scalar - Array, check type and result
        """
        self.assertIsInstance(
            2.0 - self.a_array,
            nt.NToyArray
        )
        c_array = 2.0 - self.a_array
        self.assertEqual(
            c_array[0,1],
            1.0
        )

    def test_array_minus_scalar(self):
        """
        Array - Scalar, check type and result
        """
        self.assertIsInstance(
            self.a_array - 10.0,
            nt.NToyArray
        )
        c_array = self.a_array - 10.0
        self.assertEqual(
            c_array[3,1],
            -3.0
        )

    def test_array_minus_array(self):
        """
        Array - Array, check type and result
        """
        self.assertIsInstance(
            self.a_array - self.b_array,
            nt.NToyArray
        )
        c_array = self.a_array - self.b_array
        self.assertEqual(
            c_array[3,1],
            0.0
        )

    def test_scalar_times_array(self):
        """
        Scalar * Array, check type and result
        """
        self.assertIsInstance(
            2.0 * self.a_array,
            nt.NToyArray
        )
        c_array = 2.0 * self.a_array
        self.assertEqual(
            c_array[1,0],
            4.0
        )

    def test_array_times_scalar(self):
        """
        Array * Scalar, check type and result
        """
        self.assertIsInstance(
            self.a_array * 10.0,
            nt.NToyArray
        )
        c_array = self.a_array * 10.0
        self.assertEqual(
            c_array[3,1],
            70.0
        )

    def test_array_times_array(self):
        """
        Array * Array, check type and result
        """
        self.assertIsInstance(
            self.a_array * self.b_array,
            nt.NToyArray
        )
        c_array = self.a_array * self.b_array
        self.assertEqual(
            c_array[3,1],
            49.0
        )

    def test_scalar_divided_by_array(self):
        """
        Scalar / Array, check type and result
        """
        self.assertIsInstance(
            2.0 / self.a_array,
            nt.NToyArray
        )
        c_array = 2.0 / self.a_array
        self.assertEqual(
            c_array[1,0],
            1.0
        )

    def test_array_divided_by_scalar(self):
        """
        Array / Scalar, check type and result
        """
        self.assertIsInstance(
            self.a_array / 10.0,
            nt.NToyArray
        )
        c_array = self.a_array / 10.0
        self.assertEqual(
            c_array[3,1],
            0.7
        )

    def test_array_divided_by_array(self):
        """
        Array / Array, check type and result
        """
        self.assertIsInstance(
            self.a_array / self.b_array,
            nt.NToyArray
        )
        c_array = self.a_array / self.b_array
        self.assertEqual(
            c_array[3,1],
            1.0
        )
    



