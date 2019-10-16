// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert wo rds into hash table
    while (fscanf(file, "%s", word) != EOF)  // NEW text here!
    {

        // TODO
        node *node1=malloc (sizeof(node));
        if (node1==NULL)
        {
            unload();
            return 1;
        }

        strcpy (node1->word, word);
        printf ("Word in dictionary is %s\n", node1->word);

      /*  int index = 0, words = 0;

        // Spell-check each word in text

        for (int c = fgetc(file); c != EOF; c = fgetc(file))
        {

            // Allow only alphabetical characters and apostrophes
            if (isalpha(c) || (c == '\'' && index > 0))
            {
                // Append character to word
                word[index] = c;
                index++;

                // Ignore alphabetical strings too long to be words
                if (index > LENGTH)
                {
                    // Consume remainder of alphabetical string
                    while ((c = fgetc(file)) != EOF && isalpha(c));

                    // Prepare for new word
                    index = 0;
                }
            }


             // We must have found a whole word

             else if (index > 0)
             {

                // Terminate current word
                 word[index] = '\0';

                 node *node1=malloc (sizeof(node));
                 if (node1==NULL)
                {
                     unload();
                     return 1;
                }

 //                 printf ("Word in dictionary is %s\n", word);
                  strcpy (node1->word, word);

                 // Update counter
                 words++;

                 // Prepare for next word
                 index = 0;
            }


        }
        */
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
}
