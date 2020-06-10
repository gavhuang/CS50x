#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//declare functions
int iterateArgv1(string a);

int main(int argc, string argv[]) // by default main returns int 0.
{
    // must have two argument counts and the second argument must be a non-negative
    if (argc == 2 && argv[1] >= 0 && iterateArgv1(argv[1]) == 0)
    {
        string plaintext = get_string("plaintext: ");
        printf("ciphertext: ");
        
        // next convert the plaintext to ciphertext
        for (int i = 0, n = strlen(plaintext); i < n; i++)
        {
            if (isupper(plaintext[i])) //preserve case
            {
                plaintext[i] = plaintext[i] - 65; // alphabetical index where A = 0... Z = 25
                int UpperModulo = (plaintext[i] + atoi(argv[1])) % 26; // modulo formula, remember that argv[1] is a number BUT A STRING. Use atoi() to make it an INT.
                printf("%c", UpperModulo + 65); // convert back to ASCII
            }
            else if (islower(plaintext[i])) //preserve case
            {
                plaintext[i] = plaintext[i] - 97; // alphabetical index where a = 0... z = 25
                int LowerModulo = (plaintext[i] + atoi(argv[1])) % 26;
                printf("%c", LowerModulo + 97); // convert back to ASCII
            }
            else if (ispunct(plaintext[i]) || isblank(plaintext[i]) || isdigit(plaintext[i]))
            {
                printf("%c", plaintext[i]); // just print the punctuation/digit/space
            }
        }
        printf("\n"); //print a new line
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1; // signals error
    }
}

// define function to iterate through argv[1] (the second argument of the command line)
int iterateArgv1(string a)
{
    for (int i = 0, n = strlen(a); i < n; i++)
    {
        if (isdigit(a[i]))
        {
            continue;
        }
        else
        {
            return 1; // return will stop the function.
        }
    }
    return 0; // functions requires a return. By default main returns int 0.
}