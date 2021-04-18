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

static bool realloc_memory(struct String* str)
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

void str_concat(struct String* str, const char* item)
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
            strcat(((Data*)str->internals)->data, item);
            ((Data*)str->internals)->length += strlen(item);
            return;
        }
    }
}

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

char str_get(const struct String* str, size_t index)
{
    if (index < ((Data*)str->internals)->length)
    {
        return ((Data*)str->internals)->data[index];
    }
    return -1;
}

void str_append(struct String* str, char item)
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

bool str_contains(const struct String* str, const char* item)
{
    if (strstr(((Data*)str->internals)->data, item))
    {
        return true;
    }
    return false;
}

bool str_compare(const struct String* str, const char* item)
{
    if (strcmp(((Data*)str->internals)->data, item) == 0)
    {
        return true;
    }
    return false;
}

string str_replace(const struct String* str, const char* old, const char* new)
{
    if (!str || !old || !new)
    {
        return NULL;
    }
    size_t source_len = str->Length(str);
    if (!source_len)
    {
        return NULL;
    }
    size_t old_len = strlen(old);
    if (!old_len)
    {
        return NULL;
    }
    size_t count = 0;
    const char* p = str->Text(str);
    do
    {
        p = strstr(p, old);
        if (p)
        {
            p += old_len;
            ++count;
        }
    } while (p);

    if (!count)
    {
        return str->Copy(str);
    }

    size_t source_without_old_len = source_len - count * old_len;
    size_t new_len = strlen(new);
    size_t source_with_new_len = source_without_old_len + count * new_len;
    if (new_len && ((source_with_new_len <= source_without_old_len) || (source_with_new_len + 1 == 0)))
    {
        /* Overflow. */
        return NULL;
    }

    char* result = malloc(source_with_new_len + 1);
    if (!result)
    {
        return NULL;
    }

    char* dst = result;
    const char* start_substr = str->Text(str);
    size_t i;
    for (i = 0; i != count; ++i)
    {
        const char* end_substr = strstr(start_substr, old);
        size_t substr_len = end_substr - start_substr;
        memcpy(dst, start_substr, substr_len);
        dst += substr_len;
        memcpy(dst, new, new_len);
        dst += new_len;
        start_substr = end_substr + old_len;
    }

    size_t remains = source_len - (start_substr - str->Text(str)) + 1;
    memcpy(dst, start_substr, remains);
    return create(result);
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
        str->Get = &str_get;
        str->Append = &str_append;
        str->Concat = &str_concat;
        str->Contains = &str_contains;
        str->Compare = &str_compare;
        str->Replace = &str_replace;
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