import base64
import string

import tqdm

if __name__ == '__main__':

    letters_digits = string.ascii_letters + string.digits + '='
    input_letters = set(string.printable)
    input_letters.remove('?')
    input_letters.remove('>')
    input_letters.remove('~')
    input_letters = list(input_letters)
    total = len(input_letters) ** 3
    with tqdm.tqdm(total=total) as progress:
        for a in input_letters:
            for b in input_letters:
                for c in input_letters:
                    line = f"{a}{b}{c}"
                    encoded = base64.b64encode(line.encode()).decode()
                    assert all(x in letters_digits for x in encoded), (line, encoded)

                    line = f"{a}{b}"
                    encoded = base64.b64encode(line.encode()).decode()
                    assert all(x in letters_digits for x in encoded), (line, encoded)

                    line = f"{a}"
                    encoded = base64.b64encode(line.encode()).decode()
                    assert all(x in letters_digits for x in encoded), (line, encoded)

                    progress.update()
