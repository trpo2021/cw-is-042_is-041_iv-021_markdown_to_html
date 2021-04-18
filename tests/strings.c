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

size_t str_length(const struct String* str)
{
    return ((Data*)str->internals)->length;
}

size_t str_capacity(const struct String* str)
{
    return ((Data*)str->internals)->capacity;
}

const char* str_text(const struct String* str)
{
    return ((Data*)str->internals)->data;
}

string str_copy(const struct String* str)
{
    return create(str->Text(str));
}

string init(size_t initial_capacity)
{
    if (initial_capacity > 0)
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
        str->Text = &str_text;
        str->Copy = str_copy;
        ((Data*)str->internals)->data[0] = '\0';
        return str;
    }
    return NULL;
}

string create(const char* source)
{
    if (strlen(source) > 0)
    {
        string s = init(strlen(source) + 10);
        memcpy(((Data*)s->internals)->data, source, strlen(source) + 1);
        ((Data*)s->internals)->length = strlen(source);
        return s;
    }
    else
    {
        return init(10);
    }
}