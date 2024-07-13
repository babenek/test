import binascii
import random

import tqdm

if __name__ == '__main__':

    total = 1 << 30
    match_big = 0
    match_little = 0

    with tqdm.tqdm(total=total) as progress:
        for i in range(total):
            b = random.randbytes(20)
            d = b[0:16]
            t = b[16:20]
            t_big = int.from_bytes(t, 'big')
            t_little = int.from_bytes(t, 'little')
            c = binascii.crc32(d)
            if t_big == c:
                match_big += 1
            if t_little == c:
                match_little += 1

            progress.update()
    print(total, match_big, match_big / total)
    print(total, match_little, match_little / total)
