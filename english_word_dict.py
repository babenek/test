import json
import pickle


def main():
    word_dict = {}
    with open("american-english", "r") as f:
        text = f.read()
        print("text size:", len(text))
        word_list = text.split()
        print("lines size:", len(word_list))
    word_set = set(word_list)
    for word in word_list:
        it = word_dict
        for i in word:
            if i not in it:
                it[i] = {}
            it = it[i]

    ser_list = pickle.dumps(word_dict)
    print(len(word_dict), len(ser_list))
    ser_set = pickle.dumps(word_dict)
    print(len(word_set), len(ser_set))
    print(json.dumps(word_dict))

if __name__ == "__main__":
    main()
