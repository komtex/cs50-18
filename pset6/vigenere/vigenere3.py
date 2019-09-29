import cs50
import sys

# Implements a Caesar cipher.
def main():

    # Gets key as int; validates
    cipher = sys.argv[1]

    if not cipher.isalpha or not len(sys.argv) == 2:
        exit(1)

    # Gets plaintext
    print("Plaintext: ", end="")
    ptext = cs50.get_string()

    print("Ciphertext: ", end="")

    # Counter for cipher
    n = 0

    # Enciphers while preserving case, prints
    for c in ptext:

        key = get_key(cipher, n)

        # Character is uppercase
        if c.isupper():
            upper = (((ord(c) - ord('A')) + key) % 26) + ord('A')
            print(chr(upper), end="")
            n += 1

        # Character is lowercase
        elif c.islower():
            lower = (((ord(c) - ord('a')) + key) % 26) + ord('a')
            print(chr(lower), end="")
            n += 1

        elif not c.isalpha():
            print("{}".format(c), end="")

    # Prints newline
    print()

    import sys
from cs50 import get_string


def is_valid(k):
    for ch in k:
        if not ch.isalpha():
            return False
    return True


def main():
    if len(sys.argv) != 2 or not is_valid(sys.argv[1]):
        print("Usage: ./vigenere k")
        sys.exit(1)

    k = sys.argv[1]
    plaintext = get_string("plaintext: ")
    j = 0

    print("ciphertext: ", end="")

    for ch in plaintext:
        if not ch.isalpha():
            print(ch, end="")
            continue

        ascii_offset = 65 if ch.isupper() else 97

        pi = ord(ch) - ascii_offset
        kj = ord(k[j % len(k)].upper()) - 65
        ci = (pi + kj) % 26
        j += 1

        print(chr(ci + ascii_offset), end="")

    print()

    return 0


if __name__ == "__main__":
    main()