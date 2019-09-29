from cs50 import get_string
from sys import argv
import sys


def main():

         #check command-line argument
    if len(sys.argv) != 2:
        print("Usage: python bleep.py dictionary")
        sys.exit(1)

    else:
        #load txt file
        load(argv[1])
        #prompt user input
        user_in = get_string("What message would you like to censor?")



def load(banned):
    file = open("banned.txt","r")
    words = file.read()
   print(words)
   file.close()


if __name__ == "__main__":
    main()
