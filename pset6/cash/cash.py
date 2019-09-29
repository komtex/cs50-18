from cs50 import get_float


x = 0
while True:
    n = get_float("Change owed:")
    if n > 0:
        break

coins = (round(n * 100))

while coins >= 25:
    coins = coins - 25
    x += 1
while coins >= 10:
    coins = coins - 10
    x += 1

while coins >= 5:
    coins = coins - 5
    x += 1

while coins >= 1:
    coins = coins - 1
    x += 1

print(x)