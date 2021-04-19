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

    // return copy of string length
    size_t (*Length)(const struct String* str);

    // return copy of string capacity
    size_t (*Capacity)(const struct String* str);

    // return readonly representation of string content
    const char* (*Text)(const struct String* str);

    // func to set char by index in string
    void (*Set)(const struct String* str, size_t index, char item);

    // func to get char by index in string
    char (*Get)(const struct String* str, size_t index);

    // return copy of struct
    string (*Copy)(const struct String* str);

    // free string
    void (*Free)(struct String* str);

    // concat a single char to string
    void (*Append)(struct String* str, char item);

    // concat item to string
    void (*Concat)(struct String* str, const char* item);

    // return true, if string content contains substring
    bool (*Contains)(const struct String* str, const char* item);

    // return true, if string content equals to item
    bool (*Compare)(const struct String* str, const char* item);

    // replace all substring (old) by new substring (new) in string
    string (*Replace)(const struct String* str, const char* new, const char* old);

    // return string array, splited by pattern, param length must be != null
    string* (*Split)(const struct String* str, const char* pattern, size_t* length);

    // insert item in string by index
    void (*Insert)(struct String* str, const char* item, size_t index);

    // clear string, new string equal string init(old capacity);
    void (*Clear)(struct String* str);
};

// init string with len 0, content = '\0'
string init(size_t initial_capacity);

// init string and fill with data from source
string create(const char* source);

// convert base types to char*
#define ToCharArray(buf, data, format, length)                                                                         \
    length = snprintf(NULL, 0, format, data);                                                                          \
    buf = malloc(length + 1);                                                                                          \
    snprintf(buf, length + 1, format, data);
