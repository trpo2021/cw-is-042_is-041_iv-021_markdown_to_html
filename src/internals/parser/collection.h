#pragma once

#include <stdlib.h>

/* using negitive index for storing 2 "fields" */
/* cuz our data starts from 2, we could use 0, 1 indexes in block of memory */

#define ARRAYLIST_DATA_ST 2
#define ARRAY_LIST_LENGTH_P -1
#define ARRAY_LIST_CAP_P -2

/* using: collection(type) identifier */
#define ArrayList(T) T*

/* "private" macros, using only by structure itself */

/* also, using {...} for save context */

#define array_list_set_capacity(source, size)                                                                          \
    {                                                                                                                  \
        source ? ((size_t*)(source))[ARRAY_LIST_CAP_P] = (size) : 0;                                                   \
    }

#define array_list_set_size(source, size)                                                                              \
    {                                                                                                                  \
        source ? ((size_t*)(source))[ARRAY_LIST_LENGTH_P] = (size) : 0;                                                \
    }

#define array_list_expand(source, count)                                                                               \
    {                                                                                                                  \
        size_t new_cap = ((count) * sizeof(*(source)) + (sizeof(size_t) * 2));                                         \
        if (source)                                                                                                    \
        {                                                                                                              \
            size_t* tmp = realloc(&((size_t*)(source))[ARRAY_LIST_CAP_P], new_cap);                                    \
            if (tmp)                                                                                                   \
            {                                                                                                          \
                (source) = (void*)(&tmp[ARRAYLIST_DATA_ST]);                                                           \
                array_list_set_capacity((source), (count));                                                            \
            }                                                                                                          \
        }                                                                                                              \
        else                                                                                                           \
        {                                                                                                              \
            size_t* tmp = malloc(new_cap);                                                                             \
            if (tmp)                                                                                                   \
            {                                                                                                          \
                (source) = (void*)(&tmp[ARRAYLIST_DATA_ST]);                                                           \
                array_list_set_size((source), 0);                                                                      \
                array_list_set_capacity((source), (count));                                                            \
            }                                                                                                          \
        }                                                                                                              \
    }

/* "public" macros: add, remove, free, copy */

#define ArrayListRemove(source, index)                                                                                 \
    {                                                                                                                  \
        if (source)                                                                                                    \
        {                                                                                                              \
            if ((index) < ArrayListGetLength(source))                                                                  \
            {                                                                                                          \
                array_list_set_size((source), ArrayListGetLength(source) - 1);                                         \
                for (size_t itr = (index); itr < ArrayListGetLength(source); (source)[itr] = (source)[itr + 1], itr++) \
                    ;                                                                                                  \
            }                                                                                                          \
        }                                                                                                              \
    }

#define ArrayListAdd(source, item)                                                                                     \
    {                                                                                                                  \
        if (ArrayListGetLength(source) >= ArrayListGetCapacity(source))                                                \
        {                                                                                                              \
            size_t capacity = ArrayListGetCapacity(source);                                                            \
            array_list_expand((source), !capacity ? capacity + 1 : capacity * 2);                                      \
        }                                                                                                              \
        source[ArrayListGetLength(source)] = (item);                                                                   \
        array_list_set_size((source), ArrayListGetLength(source) + 1);                                                 \
    }

#define ArrayListCopy(dest, source)                                                                                    \
    {                                                                                                                  \
        for (size_t i = 0; i < ArrayListGetLength(source);)                                                            \
            ArrayListAdd(dest, source[i++]);                                                                           \
    }

#define ArrayListFree(source)                                                                                          \
    {                                                                                                                  \
        source ? free(&((size_t*)(source))[ARRAY_LIST_CAP_P]) : 0;                                                     \
    }

/* getters */

#define ArrayListGetCapacity(source) ((source) ? ((size_t*)(source))[ARRAY_LIST_CAP_P] : (size_t)0)

#define ArrayListGetLength(source) ((source) ? ((size_t*)(source))[ARRAY_LIST_LENGTH_P] : (size_t)0)