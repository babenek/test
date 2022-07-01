#!/usr/bin/env python
import os
import sys
import atheris

# with atheris.instrument_imports(enable_loader_override=False):
#     import json


@atheris.instrument_func
def test_func(a: bytes) -> int:
    if 1<len(a):
        if 0xFF == a[0] and 0xFE == a[1]:
            return 1
        if 0xFE == a[0] and 0xFF == a[1]:
            return -1
    return 0


def fuzz_func(data):
    fdp = atheris.FuzzedDataProvider(data)
    a = fdp.ConsumeBytes(2)
    test_func(a)


def main():
#    if not os.getenv('SKIP_ATHERIS_INSTRUMENT'):
#        atheris.instrument_all()
    atheris.Setup(sys.argv + ["-max_len=2"], fuzz_func)
    atheris.Fuzz()


if __name__ == "__main__":
    main()

