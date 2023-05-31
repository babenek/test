import base64
import unittest


def proba(items):
    max_p = 0.1
    p = [0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1]
    for i in items:
        d = p[i] - max_p


class TestEntropy(unittest.TestCase):

    def test1(self):
        print (base64.b32decode('LOREMIPSUMDOLORE'))
        self.assertFalse(0)
        items = [1, 2, 3, 4, 5, 6, 7, 8, 9, 0]
        proba(items)
