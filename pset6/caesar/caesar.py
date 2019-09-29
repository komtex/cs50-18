from cs50 import get_string
from sys import argv
import sys
import cs50


def main():
    # validate right command line
    if len(sys.argv) != 2:
        print("Usage: python caesar.py k")
        sys.exit(1)
    elif sys.argv[1].isdigit == 0:
        print(f"Usage: python caesar.py k")
    # get key as int, gets plaintext
    else:
        k = int(sys.argv[1])
        s = get_string("plaintext: ")
        print("ciphertext: ", end="")
    # enciphers plaintext
    for i in range(len(s)):
        # Character is uppercase
        if str.isupper(s[i]):
            upper = (((ord(s[i]) - 65) + k) % 26) + 65
            print(chr(upper), end="")
     # Characters is lowercase
        elif str.islower(s[i]):
            lower = (((ord(s[i]) - 97) + k) % 26) + 97
            print(chr(lower), end="")
        else:
            print("{}".format(s[i]), end="")
     # print new line
    print()

# print ciphertext


if __name__ == "__main__":
    main()
