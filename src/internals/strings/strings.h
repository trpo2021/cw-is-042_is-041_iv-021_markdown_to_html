#pragma once

#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct _string
{
    void* internals;

    size_t (*length)(const struct _string* str);

    size_t (*capacity)(const struct _string* str);

    const char* (*text)(const struct _string* str);

    void (*set)(const struct _string* str, size_t index, char item);

    char (*get)(const struct _string* str, size_t index);

    struct _string* (*copy)(const struct _string* str);

    void (*free)(struct _string* str);

    void (*append)(const struct _string* str, char item);

    void (*concat)(const struct _string* str, const char* item);

    bool (*contains)(const struct _string* str, const char* item);

    bool (*compare)(const struct _string* str, const char* item);

    struct _string* (*replace)(const struct _string* str, const char* new, const char* old);

    struct _string** (*split)(const struct _string* str, const char* pattern, size_t* length);

    void (*insert)(const struct _string* str, const char* item, size_t index);

    void (*clear)(const struct _string* str);
} String;

String* init_string(size_t initial_capacity);

String* create_string(const char* source);

#define convert_to_char_array(buf, data, format, length)                                                               \
    length = snprintf(NULL, 0, format, data);                                                                          \
    buf = malloc(length + 1);                                                                                          \
    snprintf(buf, length + 1, format, data);
