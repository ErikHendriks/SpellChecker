/**
 * Implements a dictionary's functionality.
 */
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "dictionary.h"

// Root node
node* root;

// Word counter
unsigned int w;

void clean(node * ptr);

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // TODO
    int len = strlen(word);
    node* ptr = root;
    for (int i=0; i < len; i++)
    {
        char c = tolower(word[i]);
        if (c == '\'')
        {
            c = 123;
        }
        struct node* nnode = ptr->nodes[c-97];
        if (nnode == NULL)
        {
            return false;
        }
        else
        {
            ptr = nnode;
        }
    }
    if (ptr->word == true)
    {
        return true;
    }
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // TODO
    FILE* d = fopen(dictionary, "r");
    if (d == NULL)
    {
        return false;
    }
    root = calloc(1, sizeof(node));
    node* ptr = root;
    for (char c = tolower(fgetc(d)); c != EOF; c = fgetc(d))
    {
        if (c == '\n')
        {
            if (ptr != root)
            {
                w++;
                ptr->word = true;
                ptr = root;
            }
        }
        else
        {
            if (c == '\'')
            {
                c = 123;
            }
            struct node* nnode = ptr->nodes[c-97];
            if (nnode == NULL)
            {
                ptr->nodes[c-97] = calloc(1, sizeof(node));
                ptr = ptr->nodes[c-97];
            }
            else
            {
                ptr = nnode;
            }
        }
    }
    fclose(d);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return w;
}

void clean(node* ptr)
{
    for (int i = 0; i < 27; i++)
    {
        if (ptr->nodes[i] != NULL)
        {
            clean(ptr->nodes[i]);
        }
    }
    free(ptr);
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    clean(root);
    return true;
}
