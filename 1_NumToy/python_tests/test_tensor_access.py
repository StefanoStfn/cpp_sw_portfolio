"""
Test that indexing, writing and reading work correctly.
Test Constructor and creations.
"""
import unittest
import numtoy as nt

class TestTensorAccess(unittest.TestCase):

    def setUp(self):
        self.a_array = nt.NToyArray(shape=(4,3,6))
    
    def test_reading(self):
        """
        Test the reading
        """
        self.assertIsNotNone(
            self.a_array[0,1,3]
        )
        self.assertIsNotNone(
            self.a_array[0,0,0]
        )
        self.assertIsNotNone(
            self.a_array[3,2,5]
        )

    def test_writing(self):
        """
        Test writing capabilities
        """
        self.a_array[0,0,0] = 18.25
        self.assertEqual(
            self.a_array[0,0,0],
            18.25
        )
        self.a_array[1,2,3] = 99.99
        self.assertEqual(
            self.a_array[1,2,3],
            99.99
        )

    def test_creation(self):
        """
        Test constructors
        """
        self.assertIsInstance(
            nt.NToyArray(shape=(2,3)),
            nt.NToyArray
        )
        self.assertIsInstance(
            nt.NToyArray(
                shape=(2,2),
                data=[3.0, 60.087, 67.573, 190.00087]),
                nt.NToyArray
        )
        self.assertIsInstance(
            nt.NToyArray(
                shape=(2,1,2),
                data=[3.0, 60.087, 67.573, 190.00087]),
                nt.NToyArray
        )
    
