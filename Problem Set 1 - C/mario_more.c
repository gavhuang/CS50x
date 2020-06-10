#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do 
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    for (int x = 0; x < height; x++) // do this for "n" times (each row)
    {
        for (int y = 0; y < height; y++) // for "n" times (in each column of left pyramid)
        {
            if (x + y < height - 1) // for "n - 1" times, print a space, else print a #
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("  "); //print two spaces
        for (int a = 0; a <= x; a++) // finally, for each row number, print a # (this builds right pyramid)
        {
            printf("#");
        }
        printf("\n"); // this starts another row
    }
}
