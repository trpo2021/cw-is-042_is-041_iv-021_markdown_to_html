#pragma once

#include <internals/memext/memext.h>

#define ARRAY_DATA_ST 2
#define ARRAY_LENGTH_P -1
#define ARRAY_CAP_P -2

#define Array(T) T*

#define set_array_capacity(source, size)                                                                               \
    {                                                                                                                  \
        source ? ((size_t*)(source))[ARRAY_CAP_P] = (size) : 0;                                                        \
    }

#define set_array_length(source, size)                                                                                 \
    {                                                                                                                  \
        source ? ((size_t*)(source))[ARRAY_LENGTH_P] = (size) : 0;                                                     \
    }

#define expand_array(source, count)                                                                                    \
    {                                                                                                                  \
        size_t new_cap = ((count) * sizeof(*(source)) + (sizeof(size_t) * 2));                                         \
        if (source)                                                                                                    \
        {                                                                                                              \
            size_t* tmp = mem_realloc(&((size_t*)(source))[ARRAY_CAP_P], new_cap);                                     \
            (source) = (void*)(&tmp[ARRAY_DATA_ST]);                                                                   \
            set_array_capacity((source), (count));                                                                     \
        }                                                                                                              \
        else                                                                                                           \
        {                                                                                                              \
            size_t* tmp = mem_alloc(new_cap);                                                                          \
            (source) = (void*)(&tmp[ARRAY_DATA_ST]);                                                                   \
            set_array_length((source), 0);                                                                             \
            set_array_capacity((source), (count));                                                                     \
        }                                                                                                              \
    }

#define remove_array_item(source, index)                                                                               \
    {                                                                                                                  \
        if (source)                                                                                                    \
        {                                                                                                              \
            if ((index) < get_array_length(source))                                                                    \
            {                                                                                                          \
                set_array_length((source), get_array_length(source) - 1);                                              \
                for (size_t itr = (index); itr < get_array_length(source); (source)[itr] = (source)[itr + 1], itr++)   \
                    ;                                                                                                  \
            }                                                                                                          \
        }                                                                                                              \
    }

#define add_array_item(source, item)                                                                                   \
    {                                                                                                                  \
        if (get_array_length(source) >= get_array_capacity(source))                                                    \
        {                                                                                                              \
            size_t capacity = get_array_capacity(source);                                                              \
            expand_array((source), !capacity ? capacity + 1 : capacity * 2);                                           \
        }                                                                                                              \
        source[get_array_length(source)] = (item);                                                                     \
        set_array_length((source), get_array_length(source) + 1);                                                      \
    }

#define copy_array(dest, source)                                                                                       \
    {                                                                                                                  \
        for (size_t i = 0; i < get_array_length(source);)                                                              \
            add_array_item(dest, source[i++]);                                                                         \
    }

#define free_array(source)                                                                                             \
    {                                                                                                                  \
        (source) ? (free(&((size_t*)(source))[ARRAY_CAP_P])) : 0;                                                      \
    }

#define get_array_capacity(source) ((source) ? ((size_t*)(source))[ARRAY_CAP_P] : (size_t)0)

#define get_array_length(source) ((source) ? ((size_t*)(source))[ARRAY_LENGTH_P] : (size_t)0)