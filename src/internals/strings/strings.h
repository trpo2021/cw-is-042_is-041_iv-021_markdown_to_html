#pragma once

#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct _string
{
    void* internals;
} String;

String* sinit(size_t initial_capacity);

String* screate(const char* source);

size_t slength(const String* str);

size_t scapacity(const String* str);

const char* sraw(const String* str);

void sset(const String* str, size_t index, char item);

char sget(const String* str, size_t index);

void sfree(String* str);

void sclear(const String* str);

void sappend(const String* str, char item);

void sconcat(const String* str, const char* item);

void sinsert(const String* str, const char* item, size_t index);

bool scontains(const String* str, const char* item);

bool scompare(const String* str, const char* item);

String* scopy(const String* str);

String* sreplace(const String* str, const char* new, const char* old);

String** ssplit(const String* str, const char* pattern, size_t* length);

#define convert_to_char_array(buf, data, format, length)                                                               \
    length = snprintf(NULL, 0, format, data);                                                                          \
    buf = mem_alloc(length + 1);                                                                                       \
    snprintf(buf, length + 1, format, data);
