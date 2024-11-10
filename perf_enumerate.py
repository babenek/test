"""
MIT License

Copyright (c) 2024 Roman Babenko

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
import statistics
import sys
import time
from typing import List

LEN = 100
SIZE = 10000


def perf_enum_list(args):
    x = args[0]
    for i in range(SIZE):
        for n, i in x:
            assert str(n) == i


def perf_plain_list(args):
    x = args[0]
    for i in range(SIZE):
        for n, i in enumerate(x):
            assert str(n) == i


def perf_test(func, data):
    stat: List[float] = []
    for n in range(LEN):
        start_time = time.time()
        func(data)
        stat.append(time.time() - start_time)
    print(f"{func} Average = {statistics.mean(stat)} Deviation = {statistics.stdev(stat)}")


def main() -> int:
    start_time = time.time()
    l = [str(x) for x in range(10)]
    n = enumerate(l)
    perf_test(perf_enum_list, (n,))
    perf_test(perf_plain_list, (l,))
    print(f"Total time: {time.time() - start_time} SIZE={SIZE}")
    return 0


# <function perf_enum_list at 0x7076afd33d90> Average = 0.00018164873123168945 Deviation = 1.3166524916387962e-05
# <function perf_plain_list at 0x7076af15bf40> Average = 0.008094820976257324 Deviation = 0.0003013285439674138
# Total time: 0.8281574249267578 SIZE=10000

if __name__ == "__main__":
    sys.exit(main())
