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
import random
import statistics
import string
import sys
import time
from typing import List

SIZE = 2000
LEN = 1000


def replace_one(text):
    for x in text:
        line = x.replace("\\n", ' ')
        assert "\\n" not in line


def replace_two(text):
    for x in text:
        line = x.replace("\\n", '  ')
        assert "\\n" not in line


def perf_test(func, data):
    stat: List[float] = []
    for n in range(LEN):
        start_time = time.time()
        func(data)
        stat.append(time.time() - start_time)
    print(f"{func} Average = {statistics.mean(stat)} Deviation = {statistics.stdev(stat)}")


def main() -> int:
    start_time = time.time()
    random.seed(start_time.is_integer())
    data_array = []
    for x in range(SIZE):
        data_plain = ''.join(random.choices(string.printable, k=SIZE))
        data_array.append(data_plain)

    perf_test(replace_one, data_array)
    perf_test(replace_two, data_array)

    print(f"Total time: {time.time() - start_time} SIZE={SIZE}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
