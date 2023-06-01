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


def loop_loop(data):
    result = 0
    for x in data[0]:
        for y in data[1]:
            result += x.i % 3 + y.j % 5
    return result


def perf_test(func, data):
    stat: List[float] = []
    x = None
    y = None
    for n in range(LEN):
        start_time = time.time()
        x = func(data)
        stat.append(time.time() - start_time)
        if y:
            assert x == y
        else:
            y = x
    print(f"{func} Average = {statistics.mean(stat)} Deviation = {statistics.stdev(stat)}")


class D:
    def __init__(self, i):
        self.__i = i
        self.__j = i % 7

    @cached_property
    def i(self) -> int:
        return self.__i

    @cached_property
    def j(self) -> int:
        return self.__j


def main() -> int:
    start_time = time.time()

    perf_test(loop_loop, ([D(i) for i in range(1000000)], [D(i) for i in range(100)]))
    perf_test(loop_loop, ([D(i) for i in range(100)], [D(i) for i in range(1000000)]))

    print(f"Total time: {time.time() - start_time} SIZE={SIZE}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
