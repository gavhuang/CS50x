#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// declare the functions I made
int count_letters(string a);
int count_words(string a);
int count_sentences(string a);

int main(void)
{
    // prompt user for text
    string text = get_string("Text: ");

    // how many letters in the string length skipping punctuations, spaces, symbols, and digits
    int letters = count_letters(text);
    printf("%i Letter(s)\n", letters);

    // how many words in the string
    int words = count_words(text);
    printf("%i Word(s)\n", words);

    // how many sentences in the string
    int sentences = count_sentences(text);
    printf("%i Sentence(s)\n", sentences);
    
    // Coleman-Liau Index
    float L = (float) letters / ((float) words / 100); // need to cast int to a float otherwise it'll be truncated after the decimal point
    float S = (float) sentences / ((float) words / 100);
    float ColemanLiau = (0.0588 * L) - (0.296 * S) - 15.8;

    if (roundf(ColemanLiau) < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (roundf(ColemanLiau) >= 1 && roundf(ColemanLiau) <= 16) // roundf() has to be used within a function
    {
        printf("Grade %.0f\n", roundf(ColemanLiau)); // $.0f - no extra decimals after the Grade
    }
    else if (roundf(ColemanLiau) > 16)
    {
        printf("Grade 16+\n");
    }
}

// define function to count letters. The input is a string and the output is an int.
int count_letters(string a)
{
    int letters = 0; // counter at 0
    for (int i = 0, n = strlen(a); i < n; i++)
    {
        if (isalpha(a[i])) // if the character at a[i] is an alphabet letter, increase count by one.
        {
            letters++;
        }
        else // do nothing
        {
        }
    }
    return letters;
}

//define function to count words.
int count_words(string a)
{
    int words = 0; // counter at 0

    if (isalpha(a[0])) // if the first character is alphabetical, increase words by one.
    {
        words++;
    }
    else
    {
    }

    for (int i = 0, n = strlen(a); i < n; i++)
    {
        if (isblank(a[i]) && isalpha(a[i + 1])) // if the character at a[i] is a space AND the character after that is alphabetical, increase count by one.
        {
            words++;
        }
        else // do nothing
        {
        }
    }
    return words;
}

//define function to count sentences
int count_sentences(string a)
{
    int sentences = 0;

    for (int i = 0, n = strlen(a); i < n; i++)
    {
        if (a[i] == '!' || a[i] == '.' || a[i] == '?' || a[i] == ':')
        // note above: the problem set fails to say that : sound be counted as a sentence.
        {
            sentences++;
        }
        else
        {
        }
    }
    return sentences;
}