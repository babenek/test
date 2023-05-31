"""
MIT License

Copyright (c) 2023 Roman Babenko

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
"""
import random
import statistics
import sys
import time
from functools import cached_property
from typing import List

LEN = 100
SIZE = 1 << 20


class PlainProp:
    def __init__(self):
        self.test_property = random.randint(-1000, 1000)


class CacheProp:
    def __init__(self):
        self.__test_property = random.randint(-1000, 1000)

    @cached_property
    def test_property(self):
        return self.__test_property


class FuncProp:
    def __init__(self):
        self.test_property = random.randint(-1000, 1000)

    @property
    def test_property(self):
        return self.__test_property

    @test_property.setter
    def test_property(self, x):
        self.__test_property = x


def get_property(data):
    result = 0
    for i in data:
        result += i.test_property
    return result


def perf_test(func, data):
    stat: List[float] = []
    for n in range(LEN):
        start_time = time.time()
        func(data)
        stat.append(time.time() - start_time)
    print(f"{func} Average = {statistics.mean(stat)} Deviation = {statistics.stdev(stat)}")


def main() -> int:
    start_time = time.time()

    data_plain = [PlainProp()] * SIZE
    perf_test(get_property, data_plain)
    data_cached = [CacheProp()] * SIZE
    perf_test(get_property, data_cached)
    data_func = [FuncProp()] * SIZE
    perf_test(get_property, data_func)

    print(f"Total time: {time.time() - start_time} SIZE={SIZE}")
    return 0

#<function get_property at 0x7f8f8968fd90> Average = 0.030204448699951172 Deviation = 0.0009201579105806786
# <function get_property at 0x7f8f8968fd90> Average = 0.030084915161132812 Deviation = 0.0004034880426772356
# <function get_property at 0x7f8f8968fd90> Average = 0.05708320379257202 Deviation = 0.0005566302309871567
# Total time: 11.743269443511963 SIZE=1048576
#
# Process finished with exit code 0



if __name__ == "__main__":
    sys.exit(main())
