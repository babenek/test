import sys


def main(argv):
    with open("words_alpha.txt", "r") as f:
        all_lines = f.read().splitlines()
    lines3 = []
    lines = []
    for i in all_lines:
        if 3 == len(i):
            lines3.append(i)
        elif 3 < len(i):
            lines.append(i)
    print(lines3)
    print(len(lines3))
    filtered_lines = []
    for i in lines:
        for x in lines3:
            if x in i:
                break
        else:
            filtered_lines.append(i)
        print(i)

    print(len(filtered_lines))


if __name__ == """__main__""":
    main(sys.argv)
