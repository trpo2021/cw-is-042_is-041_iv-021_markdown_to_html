#pragma once

#include <stdlib.h>

/* using negitive index for storing 2 "fields" */
/* cuz our data starts from 2, we could use 0, 1 indexes in block of memory */

#define data_index 2
#define size_index -1
#define capacity_index -2

/* using: collection(type) identifier */
#define collection(T) T*

/* "private" macros, using only by structure itself */

/* also, using {...} for save context */

#define collection_set_capacity(source, size)                                                                          \
    {                                                                                                                  \
        source ? ((size_t*)(source))[capacity_index] = (size) : 0;                                                     \
    }

#define collection_set_size(source, size)                                                                              \
    {                                                                                                                  \
        source ? ((size_t*)(source))[size_index] = (size) : 0;                                                         \
    }

#define collection_expand(source, count)                                                                               \
    {                                                                                                                  \
        if (source)                                                                                                    \
        {                                                                                                              \
            size_t* tmp =                                                                                              \
                realloc(&((size_t*)(source))[capacity_index], ((count) * sizeof(*(source)) + (sizeof(size_t) * 2)));   \
            if (tmp)                                                                                                   \
            {                                                                                                          \
                (source) = (void*)(&tmp[data_index]);                                                                  \
                collection_set_capacity((source), (count));                                                            \
            }                                                                                                          \
        }                                                                                                              \
        else                                                                                                           \
        {                                                                                                              \
            size_t* tmp = malloc((count) * sizeof(*(source)) + (sizeof(size_t) * 2));                                  \
            if (tmp)                                                                                                   \
            {                                                                                                          \
                (source) = (void*)(&tmp[data_index]);                                                                  \
                collection_set_size((source), 0);                                                                      \
                collection_set_capacity((source), (count));                                                            \
            }                                                                                                          \
        }                                                                                                              \
    }

/* "public" macros: add, remove, free, copy */

#define collection_remove(source, index)                                                                               \
    {                                                                                                                  \
        if (source)                                                                                                    \
        {                                                                                                              \
            if ((index) < collection_get_size(source))                                                                 \
            {                                                                                                          \
                collection_set_size((source), collection_get_size(source) - 1);                                        \
                for (size_t itr = (index); itr < collection_get_size(source);                                          \
                     (source)[itr] = (source)[itr + 1], itr++)                                                         \
                    ;                                                                                                  \
            }                                                                                                          \
        }                                                                                                              \
    }

#define collection_add(source, item)                                                                                   \
    {                                                                                                                  \
        if (collection_get_size(source) >= collection_get_capacity(source))                                            \
        {                                                                                                              \
            size_t capacity = collection_get_capacity(source);                                                         \
            collection_expand((source), !capacity ? capacity + 1 : capacity * 2);                                      \
        }                                                                                                              \
        source[collection_get_size(source)] = (item);                                                                  \
        collection_set_size((source), collection_get_size(source) + 1);                                                \
    }

#define collection_copy(dest, source)                                                                                  \
    {                                                                                                                  \
        for (size_t i = 0; i < collection_get_size(source);)                                                           \
            collection_add(dest, source[i++]);                                                                         \
    }

#define collection_free(source)                                                                                        \
    {                                                                                                                  \
        source ? free(&((size_t*)(source))[capacity_index]) : 0;                                                       \
    }

/* getters */

#define collection_get_capacity(source) ((source) ? ((size_t*)(source))[capacity_index] : (size_t)0)

#define collection_get_size(source) ((source) ? ((size_t*)(source))[size_index] : (size_t)0)