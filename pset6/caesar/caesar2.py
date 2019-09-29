import cs50
import sys

# Implements a Caesar cipher.
def main():

    # Gets key as int; validates
    while True:
        key = int(sys.argv[1])
        if key > 0:
            break

    # Gets plaintext
    print("Plaintext: ", end="")
    ptext = cs50.get_string()

    print("Ciphertext: ", end="")

    # Enciphers while preserving case
    for i in range(len(ptext)):

        # Character is uppercase
        if str.isupper(ptext[i]):
            upper = (((ord(ptext[i]) - 65) + key) % 26) + 65
            print(chr(upper), end="")

        # Character is lowercase
        elif str.islower(ptext[i]):
            lower = (((ord(ptext[i]) - 97 ) + key ) % 26 ) + 97
            print(chr(lower), end="")

        else:
            print("{}".format(ptext[i]), end="")

    # Prints newline
    print()

# print ciphertext

if __name__ == "__main__":
    main()
