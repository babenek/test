#!/usr/bin/env python
import re
import sys
import atheris


def test_func(a: str) -> float:
    if "magic number is " == a[:16] and " parrots" == a[-8:]:
        try:
            n = int((a[-10:])[0:2])
        except Exception:
            return 0
        return 1 / (42 - n)
    return 0


def fuzz_func(data):
    fdp = atheris.FuzzedDataProvider(data)
    a = fdp.ConsumeString(256)
    test_func(a)


def main():
    atheris.instrument_all()
    atheris.Setup(sys.argv + ["-max_len=258", "-verbosity=1", "corpus/"], fuzz_func)
    atheris.Fuzz()


if __name__ == "__main__":
    # test_func("magic number is 42 parrots")
    main()

