// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 5381 //I changed the hash function for the faster one. The first one was N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;


// Represents a hash table
node *hashtable[N];

int count_dictionary = 0; //number of words in dictionary


// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;  // this is djb2 hash function
    int c = *word++;
    while (c != 0)
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        c = *word++;

    }

    return (hash % 5381);  //I decided to limit by 5381. In comparison to the staff solution, it gives me 0.01 difference in "TIME IN check"

    /*
    return tolower(word[0]) - 'a';  // the old hash function
    */
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

        node *newNode = malloc(sizeof(node)); //new memory for linked list element


        if (newNode == NULL)
        {
            unload();
            return 1;
        }

        count_dictionary++; //how many words we have

        int index_for_hash = hash(word);  //to decide what linked list we need

        strcpy(newNode->word, word); //copy the value to the linked list


        if (hashtable[index_for_hash] != NULL)  //if we already have nodes
        {
            newNode->next = hashtable[index_for_hash];   //we added a link to the previous node
            hashtable[index_for_hash] = newNode;  // the word value starts to be a new node
        }
        else  // if our list is empty
        {
            newNode->next = NULL;
            hashtable[index_for_hash] = newNode;
        }

    }

    // Close dictionary
    fclose(file);


    //  printf ("Word in dictionary is %i\n", count_dictionary);


    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (count_dictionary != 0)
    {
        return count_dictionary;
    }
    else
    {
        return 0;
    }
}

// Returns true if word is in dictionary else false
bool check(const char *word)  //from the speller "bool misspelled = !check(word)"
{


    char modify_word [LENGTH + 1]; //to make the word lowercase
    strcpy(modify_word, word);

    for (int i = 0; i < strlen(modify_word); i++)
    {
        modify_word[i] = tolower(modify_word[i]);

    }

    int index_for_hash = hash(modify_word); //where to search the word
    node *cursor =  hashtable[index_for_hash];
    while (cursor != NULL)
    {
        if (strcmp(modify_word, cursor->word) == 0)
        {
            //        printf("The founded word is %s\n", word);
            return true;
        }
        cursor = cursor->next;
    }


    return false;
}

// Unloads dictionary from memory, returning true if successful else false

bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = hashtable[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}


