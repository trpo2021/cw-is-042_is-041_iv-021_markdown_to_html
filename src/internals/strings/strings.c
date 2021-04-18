#include <internals/strings/strings.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    // char array
    char* data;
    size_t length;
    size_t capacity;
} Data;

size_t str_length(const struct String* str)
{
    return ((Data*)str->internals)->length;
}

size_t str_capacity(const struct String* str)
{
    return ((Data*)str->internals)->capacity;
}

string init(size_t initial_capacity)
{
    string str = malloc(sizeof(struct String));
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
    str->Capacity = &str_capacity;
    str->Length = &str_length;
    ((Data*)str->internals)->data[0] = '\0';
    return str;
}
