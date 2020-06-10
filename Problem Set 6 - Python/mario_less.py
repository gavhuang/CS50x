from cs50 import get_int

# Python does not have a do-while loop

def get_height():
    while True:
        n = get_int("Height: ")
        if n >= 1 and n <= 8:
            break
    return n

n = get_height()

for i in range(n):
    for j in range(n):
        if (i + j) < (n - 1):
            print(" ", end="")
        else:
            print("#", end="")
    print()