from cs50 import get_string
from sys import argv
import sys


def main():
    words = 0
         #check command-line argument
    if len(sys.argv) != 2:
        print("Usage: python bleep.py dictionary")
        sys.exit(1)

    else:
        #load txt file
        load(argv[1])
        #prompt user input
        user_in = get_string("What message would you like to censor?")



        #tokenize input
        tokens = user_in.split()

        #check with txt
    for i in tokens:
        if check(i):
            for j in i:
                print("*", end="")
        else:
            print(i, end="")
        print(" ", end="")

    return True

def load(banned):
    #load word in txt file
    file = open(banned, "r")
    for line in file:
        words.add(line.rstrip("\n"))
    file.close()
    return True

def check(word):
    #Return true if word is in dictionary else false
    return word.lower() in words



if __name__ == "__main__":
    main()
