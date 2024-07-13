import random
import statistics
from typing import List

stat: List[int] = []
for n in range(1000000):
    value = str(random.randint(10 ** 16, 10 ** 17))
    s = 0
    for n in range(0, 16):
        x = int(value[n])
        if 0 == (1 & n):  # Only for odd numbers (with 0 as a start index)
            x *= 2
            if x > 9:
                x -= 9
        s += x

    if 0 == s % 10:
        stat.append(1)
    else:
        stat.append(0)
mean = statistics.mean(stat)
print(f"Average = {mean} Deviation = {statistics.stdev(stat, mean)}")
