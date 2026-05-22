"""
This Class checks the 'fancy' features of the library.
    - MultiDim Array of Zeros
    - MultiDim Array of Ones
    - MultiDim Array of uniformly distributed random elements
    - Transpose Operation
    - Flatten operation for returning a flattened array
"""
import unittest
import numtoy as nt

class TestFeatures(unittest.TestCase):
    """
    Tests the features of the library
    """
    def setUp(self):
        """
        The 2 created Tensors have the same content
        """
        self.zero_array = nt.zeros(shape=(1,10))
        self.one_array = nt.ones(shape=(1,10))
        self.rand_array = nt.rand(
            shape=(1,400),
            min=-10.0,
            max=5.0
        )
        self.a_array = nt.NToyArray(shape=(4,2))

    def test_zeros(self):
        for i in range(10):
            self.assertEqual(
                self.zero_array[0,i],
                0.0
            )

    def test_ones(self):
        for i in range(10):
            self.assertEqual(
                self.one_array[0,i],
                1.0
            )

    def test_rand(self):
        for i in range(400):
            self.assertTrue(
                self.rand_array[0,i] < 5.0
            )
            self.assertTrue(
                self.rand_array[0,i] >= -10
            )

    def test_transpose(self):
        """
        Test transpose operation shape consistency
        and index remapping correctness.
        """
        transposed = nt.transpose(self.a_array)

        self.assertEqual(
            "(2, 4)",
            transposed.shape()
        )
        self.assertEqual(
            self.a_array[3, 1],
            transposed[1, 3]
        )

    def test_flatten(self):
        flatten_buffer = [
            0.0, 1.0,
            2.0, 3.0,
            4.0, 5.0,
            6.0, 7.0
        ]
        self.assertEqual(
            flatten_buffer,
            self.a_array.flatten()
        )

    