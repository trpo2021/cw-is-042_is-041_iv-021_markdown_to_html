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
};

string init(size_t initial_capacity);