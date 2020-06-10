#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float change;
    do
    {
        change = get_float("Change owed: ");
    }
    while (change < 0);

    // how many coins?
    int coins = round(change * 100);

    // how many quarters?
    int quarters = coins / 25;

    // changing the coins variable to become new. Basically trying to find the change.
    coins = coins - (quarters * 25);

    // how many dimes?
    int dimes = coins / 10;

    // find the change again
    coins = coins - (dimes * 10);

    // how many nickels?
    int nickels = coins / 5;

    // find the change one last time
    coins = coins - (nickels * 5);

    // how many pennies? This would be the leftover amount.
    int pennies = coins;

    printf("%i\n", quarters + dimes + nickels + pennies);
}
