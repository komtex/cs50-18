#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// prototypes
int hash(const char* word);

// define node structure
typedef struct node
{
    char *word;
    struct node* next;
} node;

// define main variables
int count = 0;
char word[LENGTH + 1];

// define hashtable
#define HASHTABLE 27
node *hashtable[HASHTABLE];

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // allocate memory to our checker
    node* checker = malloc(sizeof(node));

    // determine in which bucket is the word
    int bucket = hash(word);

    // situation of the word in our checker
    checker = hashtable[bucket];

    while (checker != NULL)
    {
        // use strcasecmp to be case insensitive
        if (strcasecmp(checker->word, word) == 0)
            return true;
        checker = checker->next;
    }
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // open the dictionnary file (reading)
    FILE* dico = fopen(dictionary, "r");

    // check if the dictionnary opens correctly
    if (dico == NULL)
        return false;

    // iterate through the dictionnary
    while (fscanf(dico, "%s\n", word) != EOF)
    {
        // initialize new node
        node *new = malloc(sizeof(node));

        // initiate first pointer
        new->word = malloc(strlen(word) + 1);

        // copy word into pointer
        strcpy(new->word, word);

        // hash the word
        int hashed = hash(word);

        // if new belongs at head, prepend
        if (hashtable[hashed] == NULL)
        {
            hashtable[hashed] = new;
            new->next = NULL;
        }

        // if belongs in middle or end
        else
        {
            new->next = hashtable[hashed];
            hashtable[hashed] = new;
        }

        // count words
        count++;
    }

    // close dictionnary
    fclose(dico);

    // that's all folks!
    return true;
}

/*
* Hash function coded thanks to CS50 Study
*/

int hash(const char* word)
{
    // initialize index to 0
    int index = 0;

    // sum ascii values
    for (int i = 0; word[i] != '\0'; i++)
        // search for lower cases words
        index += tolower(word[i]);

    // mod by size to stay w/in bound of table
    return index % HASHTABLE;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return count;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 * Coded thanks to Zamyla's instructions
 */
bool unload(void)
{
    // TODO

    for (int i = 0; i < HASHTABLE; i++)
    {
        // initiate a cursor
        node *cursor;

        // place the cursor inside the hashtable
        cursor = hashtable[i];

        while (cursor)
        {
            node* tmp = cursor;
            cursor = cursor -> next;
            free(tmp);
            return true;
        }

        // clean the hashtable
        hashtable[i] = NULL;
    }

    return false;
}


 // creates a temp variable that stores a lower-cased version of the word
    char temp[LENGTH + 1];
    int len = strlen(word);
    for(int i = 0; i < len; i++)
        temp[i] = tolower(word[i]);
    temp[len] = '\0';

    // find what index of the array the word should be in
    int index = hash(temp);

    // if hashtable is empty at index, return false
    if (hashtable[index] == NULL)
    {
        return false;
    }

    // create cursor to compare to word
    node *cursor = hashtable[index];

    // if hashtable is not empty at index, iterate through words and compare
    while (cursor != NULL)
    {
        if (strcmp(temp, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor -> next;
    }

    // if you don't find the word, return false
    return false;
}