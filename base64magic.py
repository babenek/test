import base64
import re
import string
import struct
import unittest


def gen_encoded(size, text=''):
    size -= 1
    if 0 <= size:
        for x in string.digits + string.ascii_letters:
            yield from gen_encoded(size, text + x)
    else:
        yield text


def check_asc_or_desc(line_data_value: str) -> bool:
    """ValuePatternCheck as example"""
    count_asc = 1
    count_desc = 1
    for i in range(len(line_data_value) - 1):
        if line_data_value[i] in string.ascii_letters + string.digits \
                and ord(line_data_value[i + 1]) - ord(line_data_value[i]) == 1:
            count_asc += 1
            if 4 == count_asc:
                return True
        else:
            count_asc = 1
        if line_data_value[i] in string.ascii_letters + string.digits \
                and ord(line_data_value[i]) - ord(line_data_value[i + 1]) == 1:
            count_desc += 1
            if 4 == count_desc:
                return True
        else:
            count_desc = 1
            continue
    return False


def main():
    pattern_similar = re.compile(r"(\w)\1{3,}")
    counter = 0
    for x in gen_encoded(4):
        v="pA5s"+x
        if pattern_similar.findall(v) or check_asc_or_desc(v):
            continue
        outer = sum(ord(i) for i in v)
        data = base64.b64decode(v)
        inner1, inner2, inner3 = struct.unpack("<HHH", data)
        if inner2 ^ outer == inner1 ^ inner3:
            counter += 1
            print(counter, v)


if """__main__""" == __name__:
    main()
