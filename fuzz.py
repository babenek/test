#!/usr/bin/env python
import re
import sys
import atheris


def testmycrash(input: str) -> float:
    if input[0:16] == "magic number is " and re.match('.* [0-9]+ parrots', input):
        try:
            n = int(input[-2:])
        except Exception:
            return 0
        return 1 / (42 - n)
    return 0


def fuzz_func(data):
    fdp = atheris.FuzzedDataProvider(data)
    a = fdp.ConsumeString(256)
    #print (a)
    testmycrash(a)


def main():
    atheris.instrument_all()
    atheris.Setup(sys.argv + ["-max_len=258", "-verbosity=1", "corpus/"], fuzz_func)
    atheris.Fuzz()


if __name__ == "__main__":
    main()
