#include <internals/memext/memext.h>
#include <internals/strings/strings.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    char* raw;
    size_t length;
    size_t capacity;
} Data;

static void expand_str_data(const String* str, const size_t size)
{
    ((Data*)str->internals)->capacity = size;
    ((Data*)str->internals)->raw = mem_realloc(((Data*)str->internals)->raw, (((Data*)str->internals)->capacity));
}

void sconcat(const String* str, const char* item)
{
    if (((Data*)str->internals)->length + strlen(item) + 1 >= ((Data*)str->internals)->capacity)
    {
        expand_str_data(str, (((Data*)str->internals)->length + strlen(item) + 1) * 2);
    }
    strcat(((Data*)str->internals)->raw, item);
    ((Data*)str->internals)->length += strlen(item);
}

size_t slength(const String* str)
{
    return ((Data*)str->internals)->length;
}

size_t scapacity(const String* str)
{
    return ((Data*)str->internals)->capacity;
}

const char* sraw(const String* str)
{
    return ((Data*)str->internals)->raw;
}

void sset(const String* str, size_t index, char item)
{
    if (index <= ((Data*)str->internals)->length - 1)
    {
        ((Data*)str->internals)->raw[index] = item;
    }
}

char sget(const String* str, size_t index)
{
    if (index < ((Data*)str->internals)->length)
    {
        return ((Data*)str->internals)->raw[index];
    }
    return -1;
}

void sappend(const String* str, char item)
{
    if (((Data*)str->internals)->length + 1 >= ((Data*)str->internals)->capacity)
    {
        expand_str_data(str, 1 + (((Data*)str->internals)->capacity * 2));
    }
    ((Data*)str->internals)->raw[((Data*)str->internals)->length++] = item;
    ((Data*)str->internals)->raw[((Data*)str->internals)->length] = '\0';
}

bool scontains(const String* str, const char* item)
{
    if (strstr(((Data*)str->internals)->raw, item))
    {
        return true;
    }
    return false;
}

bool scompare(const String* str, const char* item)
{
    if (strcmp(((Data*)str->internals)->raw, item) == 0)
    {
        return true;
    }
    return false;
}

String* sreplace(const String* str, const char* old, const char* new)
{
    if (!str || !old || !new)
    {
        return NULL;
    }
    char* ptr = strstr(sraw(str), old);
    if (!ptr || strlen(old) == 0)
    {
        return scopy(str);
    }
    String* out = sinit(scapacity(str));
    size_t pos = 0;
    size_t len = slength(str);
    while (ptr)
    {
        while (pos < ptr - sraw(str))
        {
            sappend(out, sget(str, pos++));
        }
        sconcat(out, new);
        ptr = strstr(ptr + strlen(old), old);
        pos += strlen(old);
    }
    while (pos < len)
    {
        sappend(out, sget(str, pos++));
    }
    return out;
}

String** ssplit(const String* str, const char* pattern, size_t* length)
{
    char* copy = mem_alloc(((Data*)str->internals)->length + 1);
    memcpy(copy, ((Data*)str->internals)->raw, ((Data*)str->internals)->length + 1);
    String** container = NULL;
    *length = 0;
    for (char* p = strtok(copy, pattern); p != NULL; p = strtok(NULL, pattern))
    {
        container = mem_realloc(container, sizeof(String*) * (++(*length)));
        container[(*length) - 1] = screate(p);
    }
    mem_free(copy);
    return container;
}

void sinsert(const String* str, const char* item, size_t index)
{
    if (slength(str) == 0)
    {
        sconcat(str, item);
        return;
    }
    if (index < ((Data*)str->internals)->length)
    {
        if (((Data*)str->internals)->capacity < ((Data*)str->internals)->length + strlen(item) + 1)
        {
            expand_str_data(str, (((Data*)str->internals)->length + strlen(item) + 1) * 2);
        }
        memmove(&((Data*)str->internals)->raw[index + strlen(item)], &((Data*)str->internals)->raw[index],
                slength(str) - index + 1);
        memmove(&((Data*)str->internals)->raw[index], item, strlen(item));
        ((Data*)str->internals)->length += strlen(item);
    }
}

String* scopy(const String* str)
{
    return screate(sraw(str));
}

void sfree(String* str)
{
    if (str)
    {
        if (str->internals)
        {
            if (((Data*)str->internals)->raw)
            {
                free(((Data*)str->internals)->raw);
                ((Data*)str->internals)->raw = NULL;
            }
            free(str->internals);
            str->internals = NULL;
        }
        free(str);
    }
}

void sclear(const String* str)
{
    if (str)
    {
        if (str->internals)
        {
            if (((Data*)str->internals)->raw)
            {
                free(((Data*)str->internals)->raw);
                ((Data*)str->internals)->raw = mem_alloc(((Data*)str->internals)->capacity);
                ((Data*)str->internals)->length = 0;
                ((Data*)str->internals)->raw[0] = '\0';
            }
        }
    }
}

String* sinit(size_t initial_capacity)
{
    if (initial_capacity > 0)
    {
        String* str = mem_alloc(sizeof(String));
        str->internals = mem_alloc(sizeof(Data));

        ((Data*)str->internals)->capacity = initial_capacity;
        ((Data*)str->internals)->raw = mem_alloc(((Data*)str->internals)->capacity);
        ((Data*)str->internals)->length = 0;

        ((Data*)str->internals)->raw[0] = '\0';
        return str;
    }
    return NULL;
}

String* screate(const char* source)
{
    if (strlen(source) > 0)
    {
        String* s = sinit(strlen(source) + 10);
        memcpy(((Data*)s->internals)->raw, source, strlen(source) + 1);
        ((Data*)s->internals)->length = strlen(source);
        return s;
    }
    return sinit(10);
}