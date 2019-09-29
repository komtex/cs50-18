
from cs50 import get_string
from sys import argv
import sys
import cs50


def main():
    # validate right command line
    if len(sys.argv) != 2 or sys.argv[1].isalpha() == 0:
        print("Usage: python vigenere.py k")
        sys.exit(1)

    # get key as int, gets plaintext
    else:
        key = sys.argv[1]
        s = get_string("plaintext: ")
        # counter for cipher
        j = 0
        print("ciphertext: ", end="")
        # Enciphers casa, print
    for i in s:
        # character is uppercase
        if i.isupper():
            upper = (((ord(i) - 65) + (ord(key[j % len(key)].upper()) - 65)) % 26) + 65
            j += 1
            print(chr(upper), end="")
            # character is lowercase
        elif i.islower():
            lower = (((ord(i) - 97) + (ord(key[j % len(key)].upper()) - 65)) % 26) + 97
            j += 1
            print(chr(lower), end="")

        elif not i.isalpha():
            print("{}".format(i), end="")
     # print new line
    print()


if __name__ == "__main__":
    main()
