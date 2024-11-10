import binascii

import multiprocessing


def run(inpt):
    for i in range(inpt[1] << 28, inpt[1] << 28 + 0x10000000):
        aug = f"{i:08x}".encode()
        data = aug + inpt[0]
        crc32 = binascii.crc32(data)
        if 0 == crc32:
            print(data)
            break
        if 0 == i & 0xFFFFFF:
            print(f"{i:08x}", aug)
    else:
        print("nope")


def main():
    with open(__file__, 'rb') as f:
        text = f.read()
    inpt = [(text, x) for x in range(16)]
    with multiprocessing.Pool(16) as p:
        for _ in p.map(run, inpt):
            pass


if __name__ == '__main__':
    main()
