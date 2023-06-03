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
import base64
import random
import statistics
import sys
import time
from functools import cached_property
from typing import List

import regex as regex

LEN = 100
SIZE = 1 << 16

r_a = regex.compile(r"(^|[^0-9A-Za-z]+)(?P<val>(([0-9A-Za-z_-]{4}){16,64})|(([0-9A-Za-z+/]{4}){16,64}))([^=0-9A-Za-z]+|$)")


def regex_a(data):
    x = 0
    for line in data:
        x += bool(r_a.search(line))
    return x


r_b = regex.compile(r"(^|[^A-Za-z0-9]+)(?P<val>(([A-Za-z0-9_-]{4}){16,64})|(([A-Za-z0-9+/]{4}){16,64}))([^=A-Za-z0-9]+|$)")


def regex_b(data):
    x = 0
    for line in data:
        x += bool(r_b.search(line))
    return x


def perf_test(func, data):
    stat: List[float] = []
    x = 0
    for n in range(LEN):
        start_time = time.time()
        x += func(data)
        stat.append(time.time() - start_time)
    print(f"{func} Average = {statistics.mean(stat)} Deviation = {statistics.stdev(stat)}")
    return x


def main() -> int:
    start_time = time.time()

    data = []
    for n in range(SIZE):
        random_data = random.randbytes(32 + 0x7f & n)
        if 0 == n % 3:
            data_enc = base64.standard_b64encode(random_data).decode('ascii')
        elif 1 == n % 3:
            data_enc = base64.urlsafe_b64encode(random_data).decode('ascii')
        else:
            data_enc = base64.b85encode(random_data).decode('ascii')
        data.append(data_enc)

    a = perf_test(regex_a, data)

    b = perf_test(regex_b, data)

    print(f"Total time: {time.time() - start_time} SIZE={SIZE}")

    assert a == b

    return 0


if __name__ == "__main__":
    sys.exit(main())


#/home/babenek/r/test/.venv/bin/python /home/babenek/r/test/corpus/perf_regex.py
# <function regex_a at 0x7f2a8e9cf1c0> Average = 0.5477575302124024 Deviation = 0.021110702883208796
# <function regex_b at 0x7f2a8e8b0940> Average = 0.5548891353607178 Deviation = 0.02378513814976043
# Total time: 110.41043090820312 SIZE=65536
