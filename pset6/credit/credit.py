from cs50 import get_int
from math import floor
from cs50 import get_string


def main():
    digit1 = 0
    digit2 = 0
    num_digits = 0
    double_odds = 0
    evens = 0
    numbers = get_int("Number: ")

    while numbers > 0:
        # first and second digits at the beginning are equals
        digit2 = digit1
        digit1 = numbers % 10
        # multiply each second digit and sum odd and even
        if num_digits % 2 == 0:
            evens += digit1
        else:
            m = 2 * digit1
            double_odds += (m // 10) + (m % 10)
        # loop till the end of digits
        numbers //= 10
        num_digits += 1
        # test for validity by dividing to 10
    is_valid = (evens + double_odds) % 10 == 0
    first_two_digits = (digit1 * 10) + digit2

    if digit1 == 4 and num_digits >= 13 and num_digits <= 16 and is_valid:
        print("VISA\n")
    elif first_two_digits >= 51 and first_two_digits <= 55 and num_digits == 16 and is_valid:
        print("MASTERCARD\n")
    elif (first_two_digits == 34 or first_two_digits == 37) and num_digits == 15 and is_valid:
        print("AMEX\n")
    else:
        print("INVALID\n")


if __name__ == "__main__":
    main()