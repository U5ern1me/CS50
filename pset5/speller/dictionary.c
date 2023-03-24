// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 45 * 26;

// Hash table
node *table[N], *n = NULL;

long count = 0; // Stores number of words in dictionary
int num = 0; //To use as index variable in arrays
char str[LENGTH + 1] = " "; // Stores word in lowercase
bool flag = false; // To store if dictionary has been opened

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    for(num = 0; word[num] != '\0'; num++)
        str[num] = tolower(word[num]);
    str[num] = '\0'; // End of string
    for (n = table[hash(str)]; n != NULL; n = n->next)
    {
        num = strcmp(n->word, str);
        if (num > 0); // If str comes alphabetically before n->word
        else
            return (num == 0) ? true : false;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    if (isalpha(word[1])) // If second letter of word is an alphabet
        return 28 * (word[0] - 97) + word[1] - 95;
    else if (word[1] == '\'') // If second letter of word is an apostrophe
        return 28 * (word[0] - 97) + 1;
    else // If second letter of word is null character, i.e. it is a one letter word
        return 28 * (word[0] - 97);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
        return false;
    char c; // To store each letter of dictionary word
    for(int i = 0; i < N; i++)
        table[i] = NULL;
    while (fread(&c, 1, 1, file))
    {
        if (c != '\n') // End of word
            str[num++] = c;
        else
        {
            str[num] = '\0';
            count++;
            
            if (isalpha(str[1]))
                num = 28 * (str[0] - 97) + str[1] - 95;
            else if (str[1] == '\'')
                num = 28 * (str[0] - 97) + 1;
            else
                num = 28 * (str[0] - 97);
            
            /*
            num = 0;
            for (int i = 0; str[i] != '\0'; i++)
                if (str[i] != '\'')
                    num += str[i] - 96;
            */
            
            n = malloc(sizeof(node));
            if (n == NULL)
                return false;
            strcpy(n->word, str);
            n->next = NULL;
            if (table[num] != NULL)
                n->next = table[num];
            table[num] = n;
            num = 0;
        }
    }
    fclose(file);
    flag = true;
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return (flag) ? count : 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *tmp = NULL;
    for (int i = 0; i < N; i++)
    {
        n = table[i];
        table[i] = NULL;
        while (n != NULL)
        {
            tmp = n->next;
            free(n);
            n = tmp;
        }
    }
    return true;
}