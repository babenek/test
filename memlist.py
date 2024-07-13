import base64
import random
from dataclasses import dataclass


@dataclass(frozen=True)
class A:
    lines: list[str]


# class A:
#     def __init__(self,a):
#         self.lines: list[str] = a


def main():
    lines = []
    for n in range(10000):
        lines.append(base64.b64encode(random.randbytes(80)).decode())

    aaa = []
    for n in range(100000):
        for i in lines:
            aaa.append(i)
    assert 0 < len(aaa)

    bbb = []
    for b in aaa:
        bbb.append(b)
    assert len(aaa) == len(bbb)


if __name__ == "__main__":
    main()
