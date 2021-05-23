#include <../src/internals/strings/strings.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    // char array
    char* data;
    size_t length;
    size_t capacity;
} Data;

static bool realloc_memory(const struct _string* str)
{
    ((Data*)str->internals)->capacity = 1 + (((Data*)str->internals)->capacity * 2);
    char* temp = realloc(((Data*)str->internals)->data, (((Data*)str->internals)->capacity));
    if (!temp)
    {
        return false;
    }
    ((Data*)str->internals)->data = temp;
    return true;
}

void str_concat(const struct _string* str, const char* item)
{
    if (((Data*)str->internals)->length + strlen(item) + 1 < ((Data*)str->internals)->capacity)
    {
        strcat(((Data*)str->internals)->data, item);
        ((Data*)str->internals)->length += strlen(item);
    }
    else
    {
        char* temp = realloc(((Data*)str->internals)->data, (((Data*)str->internals)->length + strlen(item) + 1) * 2);
        if (temp)
        {
            ((Data*)str->internals)->data = temp;
            strcat(((Data*)str->internals)->data, item);
            ((Data*)str->internals)->capacity = (((Data*)str->internals)->length + strlen(item) + 1) * 2;
            ((Data*)str->internals)->length += strlen(item);
            return;
        }
    }
}

size_t str_length(const struct _string* str)
{
    return ((Data*)str->internals)->length;
}

size_t str_capacity(const struct _string* str)
{
    return ((Data*)str->internals)->capacity;
}

const char* str_text(const struct _string* str)
{
    return ((Data*)str->internals)->data;
}

void str_set(const struct _string* str, size_t index, char item)
{
    if (index > ((Data*)str->internals)->length - 1)
    {
        return;
    }
    ((Data*)str->internals)->data[index] = item;
}

char str_get(const struct _string* str, size_t index)
{
    if (index < ((Data*)str->internals)->length)
    {
        return ((Data*)str->internals)->data[index];
    }
    return -1;
}

void str_append(const struct _string* str, char item)
{
    if (((Data*)str->internals)->length + 1 < ((Data*)str->internals)->capacity)
    {
        ((Data*)str->internals)->data[((Data*)str->internals)->length++] = item;
        ((Data*)str->internals)->data[((Data*)str->internals)->length] = '\0';
        return;
    }
    if (realloc_memory(str))
    {
        ((Data*)str->internals)->data[((Data*)str->internals)->length++] = item;
        ((Data*)str->internals)->data[((Data*)str->internals)->length] = '\0';
        return;
    }
}

bool str_contains(const struct _string* str, const char* item)
{
    if (strstr(((Data*)str->internals)->data, item))
    {
        return true;
    }
    return false;
}

bool str_compare(const struct _string* str, const char* item)
{
    if (strcmp(((Data*)str->internals)->data, item) == 0)
    {
        return true;
    }
    return false;
}

String* str_replace(const struct _string* str, const char* old, const char* new)
{
    if (!str || !old || !new)
    {
        return NULL;
    }
    char* ptr = strstr(str->text(str), old);
    if (!ptr || strlen(old) == 0)
    {
        return str->copy(str);
    }
    String* out = init_string(str->capacity(str));
    size_t pos = 0;
    while (ptr)
    {
        for (; pos < ptr - str->text(str); ++pos)
        {
            out->append(out, str->get(str, pos));
        }
        out->concat(out, new);
        ptr = strstr(ptr + strlen(old), old);
        pos += strlen(old);
    }
    for (; pos < str->length(str); ++pos)
    {
        out->append(out, str->get(str, pos));
    }
    return out;
}

String** str_split(const struct _string* str, const char* pattern, size_t* length)
{
    char* copy = malloc(((Data*)str->internals)->length + 1);
    memcpy(copy, ((Data*)str->internals)->data, ((Data*)str->internals)->length + 1);
    String** container = NULL;
    *length = 0;
    for (char* p = strtok(copy, pattern); p != NULL; p = strtok(NULL, pattern))
    {
        String** temp = realloc(container, sizeof(String*) * (++(*length)));
        if (temp)
        {
            container = temp;
            container[(*length) - 1] = create_string(p);
        }
    }
    free(copy);
    return container;
}

void str_insert(const struct _string* str, const char* item, size_t index)
{
    if (str->length(str) == 0)
    {
        str->concat(str, item);
        return;
    }
    if (index < ((Data*)str->internals)->length)
    {
        if (((Data*)str->internals)->capacity < ((Data*)str->internals)->length + strlen(item) + 1)
        {
            char* temp =
                realloc(((Data*)str->internals)->data, (((Data*)str->internals)->length + strlen(item) + 1) * 2);
            if (temp)
            {
                ((Data*)str->internals)->capacity = (((Data*)str->internals)->length + strlen(item) + 1) * 2;
                ((Data*)str->internals)->data = temp;
            }
        }
        memmove(&((Data*)str->internals)->data[index + strlen(item)], &((Data*)str->internals)->data[index],
                str->length(str) - index + 1);
        memmove(&((Data*)str->internals)->data[index], item, strlen(item));
        ((Data*)str->internals)->length += strlen(item);
    }
}

String* str_copy(const struct _string* str)
{
    return create_string(str->text(str));
}

void str_free(struct _string* str)
{
    if (str)
    {
        if (str->internals)
        {
            if (((Data*)str->internals)->data)
            {
                free(((Data*)str->internals)->data);
                ((Data*)str->internals)->data = NULL;
            }
            free(str->internals);
            str->internals = NULL;
        }
        free(str);
    }
}

void str_clear(const struct _string* str)
{
    if (str)
    {
        if (str->internals)
        {
            if (((Data*)str->internals)->data)
            {
                free(((Data*)str->internals)->data);
                ((Data*)str->internals)->data = malloc(((Data*)str->internals)->capacity);
                ((Data*)str->internals)->length = 0;
                ((Data*)str->internals)->data[0] = '\0';
            }
        }
    }
}

String* init_string(size_t initial_capacity)
{
    if (initial_capacity > 0)
    {
        String* str = malloc(sizeof(String));
        if (!str)
        {
            return NULL;
        }
        str->internals = malloc(sizeof(Data));
        if (!str->internals)
        {
            free(str);
            return NULL;
        }
        ((Data*)str->internals)->capacity = initial_capacity;
        ((Data*)str->internals)->data = malloc(((Data*)str->internals)->capacity);
        if (!((Data*)str->internals)->data)
        {
            free(str->internals);
            free(str);
            return NULL;
        }
        ((Data*)str->internals)->length = 0;
        str->capacity = &str_capacity;
        str->length = &str_length;
        str->text = &str_text;
        str->copy = &str_copy;
        str->free = &str_free;
        str->set = &str_set;
        str->get = &str_get;
        str->append = &str_append;
        str->concat = &str_concat;
        str->contains = &str_contains;
        str->compare = &str_compare;
        str->replace = &str_replace;
        str->split = &str_split;
        str->insert = &str_insert;
        str->clear = &str_clear;
        ((Data*)str->internals)->data[0] = '\0';
        return str;
    }
    return NULL;
}

String* create_string(const char* source)
{
    if (strlen(source) > 0)
    {
        String* s = init_string(strlen(source) + 10);
        memcpy(((Data*)s->internals)->data, source, strlen(source) + 1);
        ((Data*)s->internals)->length = strlen(source);
        return s;
    }
    else
    {
        return init_string(10);
    }
}