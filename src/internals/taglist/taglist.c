#include <internals/taglist/taglist.h>

unsigned int hashtab_hash(char* key)
{
    unsigned int h = 0, hash_mul = 31;
    while (*key)
        h = h * hash_mul + (unsigned int)*key++;
    return h % HASHTAB_SIZE;
}

void hashtab_init(Tag** hashtab)
{
    for (int i = 0; i < HASHTAB_SIZE; i++)
        hashtab[i] = NULL;
}

void hashtab_add(Tag** hashtab, char* key, char* value)
{
    Tag* node;
    int index = hashtab_hash(key);

    node = malloc(sizeof(*node));
    if (node != NULL)
    {
        strcpy(node->key, key);
        strcpy(node->value, value);
        node->next = hashtab[index];
        hashtab[index] = node;
    }
}

Tag* hashtab_lookup(Tag** hashtab, char* key)
{
    Tag* node;

    int index = hashtab_hash(key);
    for (node = hashtab[index]; node != NULL; node = node->next)
    {
        if (0 == strcmp(node->key, key))
            return node;
    }
    return NULL;
}

void hashtab_delete(Tag** hashtab, char* key)
{
    Tag *node, *prev = NULL;
    int index = hashtab_hash(key);
    for (node = hashtab[index]; node != NULL; node = node->next)
    {
        if (0 == strcmp(node->key, key))
        {
            if (prev == NULL)
                hashtab[index] = node->next;
            else
                prev->next = node->next;
            free(node);
            return;
        }
        prev = node;
    }
}

void create_taglist(Tag** map)
{
    TagList list = {.tags[0] = {"# ", "<h1>"},
                    .tags[1] = {"=", "<h1>"},
                    .tags[2] = {"-", "<h2>"},
                    .tags[3] = {"## ", "<h2>"},
                    .tags[4] = {"### ", "<h3>"},
                    .tags[5] = {"#### ", "<h4>"},
                    .tags[6] = {"##### ", "<h5>"},
                    .tags[7] = {"######", "<h6>"},
                    .tags[8] = {"**", "<strong>"},
                    .tags[9] = {"__", "<strong>"},
                    .tags[10] = {"*", "<em>"},
                    .tags[11] = {"_", "<em>"},
                    .tags[12] = {"***", "<strong>"},
                    .tags[13] = {"___", "<strong>"},
                    .tags[14] = {"  \n\n", "<br>"},
                    .tags[15] = {">", "<blockquote>"},
                    .tags[16] = {">>", "<blockquote>"},
                    .tags[17] = {">>>", "<blockquote>"},
                    .tags[18] = {"1.", "<ol><li>"},
                    .tags[19] = {"1)", "<ol><li>"},
                    .tags[20] = {"- ", "<ul><li>"},
                    .tags[21] = {"* ", "<ul><li>"},
                    .tags[22] = {"+ ", "<ul><li>"},
                    .tags[23] = {"        ", "<code>"},
                    .tags[24] = {"***", "<hr>"},
                    .tags[25] = {"---", "<hr>"},
                    .tags[26] = {"___", "<hr>"},
                    .tags[27] = {"`", "<code>"},
                    .tags[28] = {"    ", "<code>"}};

    hashtab_init(map);
    for (int i = 0; i < 29; i++)
    {
        hashtab_add(map, list.tags[i].key, list.tags[i].value);
    }
}