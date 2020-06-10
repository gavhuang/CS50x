from cs50 import get_float
import math

def change():
    while True:
        change = get_float("Change owed: ")
        if change > 0:
            break
    return change

# Run program and round
# Unlike C, where I declared int, I have to round down using math module
change = change()
coins = change * 100

# How many quarters?
quarters = math.floor(coins / 25)
coins = coins - (quarters * 25)

# How many dimes?
dimes = math.floor(coins / 10)
coins = coins - (dimes * 10)

# How many nickels?
nickels = math.floor(coins / 5)
coins = coins - (nickels * 5)

# What's leftover?
pennies = math.floor(coins)

print(quarters + dimes + nickels + pennies)