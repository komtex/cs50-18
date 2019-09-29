// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 27
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;
int count = 0;
// Represents a hash table
node *hashtable[N] = {NULL};


// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
   int index = 0;
   for (int i=0; word[i] != '\0'; i++)
   index += tolower(word[i]);
   return index % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s\n", word) != EOF)
    {
        count ++;
       node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            unload();
            return false;
        }
       strcpy(new_node -> word, word);
       int index = hash(word);
       // if hashtable is empty at index, insert
       if (hashtable[index] == NULL)
       {
           hashtable[index] = new_node;
           new_node -> next = NULL;
       }
        else
        {
            new_node -> next = hashtable[index];
            hashtable[index] = new_node;
        }
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    //if dictionary is loaded return number of word
   if (count > 0)
   return count;
   else
   return 0;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{

 // allocate memory to our checker
    node *checker = malloc(sizeof(node));

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

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
   // create a variable to go through index
    int index = 0;

    // iterate through entire hashtable array
    while (index < N)
    {
        // if hashtable is empty at index, go to next index
        if (hashtable[index] == NULL)
        {
            index++;
        }

        // if hashtable is not empty, iterate through nodes and start freeing
        else
        {
            while(hashtable[index] != NULL)
            {
                node *cursor = hashtable[index];
                hashtable[index] = cursor -> next;
                free(cursor);
            }

            // once hashtable is empty at index, go to next index
            index++;
        }
    }

    return true;
}
