import random

from tqdm import tqdm


def main():
    triplet = 0
    thrice = 0
    cnt = 10 ** 9
    for _ in tqdm(range(cnt)):
        if random.randint(1, 216) == 5:
            triplet += 1
        if random.randint(1, 6) == 5 and random.randint(1, 6) == 5 and random.randint(1, 6) == 5:
            thrice += 1

    print(triplet / cnt)
    print(thrice / cnt)


if __name__ == """__main__""":
    main()
