

from cs50 import get_int


while True:
    n = get_int("height:")
    if n > 0 and n <= 8:
        break


for i in range(n):

    for j in range(i, n-1):
        print(" ", end="")
    for k in range(n, i+n+1):
        print("#", end="")
    print()
