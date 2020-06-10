// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table (26x26)
const unsigned int N = 676;

// Hash table
node *table[N];

// Declare hash function to use in check()
unsigned int hash(const char *word);

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Store in memory lowercase word to hash
    // Hashing uppercase letters will cause different hash values

    int n = strlen(word);
    char lower_word[n + 1];

    // n + 1 because you need to copy the '\0'
    for (int i = 0; i < n + 1; i++)
    {
        lower_word[i] = tolower(word[i]);
    }

    // Hash the lowercase word, set a cursor to where it would be in the dictionary table
    int i = hash(lower_word);

    // You don't need malloc cursor because table exists in memory already
    node *cursor = table[i];

    // Keep going until cursor reaches NULL
    while (cursor != NULL)
    {
        // Compare the word to the cursor's word
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    return false;
}

// Hashes word to a number
// Hash source: http://www.cse.yorku.ca/~oz/hash.html
// Add % N as mentioned in the short since the hash would exceed the size of the table
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash % N;
}

// Count the number of loads for size()
int load_number = 0;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary
    FILE *file = fopen(dictionary, "r");

    if (!file)
    {
        return false;
    }

    // Read strings from file
    // Scan file, each string is 1 word. char word[LENGTH + 1] is a buffer
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) == 1)
    {
        // Create a temp node for each word
        // Allocate enough memory for the node
        node *n = malloc(sizeof(node));
        // Check for memory allocation failure
        if (n == NULL)
        {
            return false;
        }
        // Copy the word into the node: strcpy(destination, source)
        strcpy(n->word, word);
        n->next = NULL;

        // Hash this word to figure out where it goes in the table
        int i = hash(word);

        // Insert node into front of hash table
        // Point temp node n to the head of the table. Then point the table to n.
        n->next = table[i];
        table[i] = n;
        load_number++;
    }
    // Memory leak if file not closed.
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return load_number;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Need to free the hash table from memory
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            node *cursor = table[i];
            node *tmp = table[i];

            while (cursor != NULL)
            {
                cursor = cursor->next;
                free(tmp);
                tmp = cursor;
            }
        }
    }
    return true;
}