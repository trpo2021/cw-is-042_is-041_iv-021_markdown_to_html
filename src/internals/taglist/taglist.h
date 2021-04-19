#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASHTAB_SIZE 100

typedef struct tag Tag;

struct tag
{
    char key[100];
    char value[100];
    Tag* next;
};

typedef struct
{
    Tag tags[100];
} TagList;

unsigned int hashtab_hash(char* key);
void hashtab_init(Tag** hashtab);
void hashtab_add(Tag** hashtab, char* key, char* value);
void create_taglist(Tag** map);
Tag* hashtab_lookup(Tag** hashtab, char* key);
void hashtab_delete(Tag** hashtab, char* key);