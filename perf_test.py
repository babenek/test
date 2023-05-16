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
import math
import random
import statistics
import sys
import time
from typing import List

LEN = 100
SIZE = 1 << 20


def test_func(i):
    return 42 == math.sqrt(i)


def perf_test_any_return(data):
    if any(test_func(i) for i in data):
        return True
    return False


def perf_test_for_return(data):
    for i in data:
        if test_func(i):
            return True
    return False


def perf_test_any_break(data):
    result = False
    if any(test_func(i) for i in data):
        result = True
    return result


def perf_test_for_break(data):
    result = False
    for i in data:
        if test_func(i):
            result = True
            break
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
    data = [random.randint(0, 1 << 32) for i in range(SIZE)]
    perf_test(perf_test_any_return, data)
    perf_test(perf_test_for_return, data)
    perf_test(perf_test_any_break, data)
    perf_test(perf_test_for_break, data)
    print(f"Total time: {time.time() - start_time} SIZE={SIZE}")
    return 0

# results:
# <function perf_test_any_return at 0x7f068cfeb910> Average = 0.11843196153640748 Deviation = 0.0015744642316259244
# <function perf_test_for_return at 0x7f068cfeba30> Average = 0.10853729486465453 Deviation = 0.0006816465047585867
# <function perf_test_any_break at 0x7f068cfebc70> Average = 0.11445562362670898 Deviation = 0.0023068645681618496
# <function perf_test_for_break at 0x7f068d0349d0> Average = 0.10444020032882691 Deviation = 0.0019803037085437195
# Total time: 45.11462354660034 SIZE=1048576


if __name__ == "__main__":
    sys.exit(main())
