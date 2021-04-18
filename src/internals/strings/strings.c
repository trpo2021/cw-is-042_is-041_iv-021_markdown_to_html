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

void str_set(const struct String* str, size_t index, char item)
{
    if (index > ((Data*)str->internals)->length - 1)
    {
        return;
    }
    ((Data*)str->internals)->data[index] = item;
}

string str_copy(const struct String* str)
{
    return create(str->Text(str));
}

void str_free(struct String* str)
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
        str->Copy = &str_copy;
        str->Free = &str_free;
        str->Set = &str_set;
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