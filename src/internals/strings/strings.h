#pragma once

#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct String* string;

struct String
{
    // private data
    void* internals;

    /* public interface */

    // props
    size_t (*Length)(const struct String* str);
    size_t (*Capacity)(const struct String* str);
    const char* (*Text)(const struct String* str);
    void (*Set)(const struct String* str, size_t index, char item);
    char (*Get)(const struct String* str, size_t index);
    // methods
    string (*Copy)(const struct String* str);
    void (*Free)(struct String* str);
    void (*Append)(struct String* str, char item);
    void (*Concat)(struct String* str, const char* item);
    bool (*Contains)(const struct String* str, const char* item);
    bool (*Compare)(const struct String* str, const char* item);
    string (*Replace)(const struct String* str, const char* new, const char* old);
    string* (*Split)(const struct String* str, const char* pattern, size_t* length);
    void (*Insert)(struct String* str, const char* item, size_t index);
};

string init(size_t initial_capacity);

string create(const char* source);