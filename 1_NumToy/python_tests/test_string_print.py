"""
Testing the printable features
    - version
    - Tensor shape
    - Tensor Content
"""
import unittest
import numtoy as nt

class TestStringPrint(unittest.TestCase):
    """
    Testing everything that can be represented with the library
    """
    def setUp(self):
        """
        Two arrays are instantiated for testing
        """
        self.a_array = nt.NToyArray(shape=(4,2))
        self.b_array = nt.NToyArray(shape=(2,2,2))

    def test_shape(self):
        """
        testing the shape method
        """
        self.assertEqual(
            "(4, 2)",
            self.a_array.shape()
        )
        self.assertEqual(
            "(2, 2, 2)",
            self.b_array.shape()
        )

    def test_version(self):
        """
        Version is 1.0.0 and always be that.
        """
        self.assertEqual(
            nt.version(),
            "1.0.0"
        )

    def test_print_array(self):
        """
        Testing Array Representations __repr__
        """
        tmp_string = "NToyArray([[0.000000,1.000000],[2.000000,3.000000],"
        tmp_string += "[4.000000,5.000000],[6.000000,7.000000]], dtype=double)"
        self.assertEqual(
            tmp_string,
            str(self.a_array)
        )
        tmp_string = "NToyArray([[[0.000000,1.000000],[2.000000,3.000000]],"
        tmp_string += "[[4.000000,5.000000],[6.000000,7.000000]]], dtype=double)"
        self.assertEqual(
            tmp_string,
            str(self.b_array)
        )

