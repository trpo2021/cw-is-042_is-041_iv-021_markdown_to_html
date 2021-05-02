#include <ctest.h>
#include <internals/parser/collection.h>
#include <stdio.h>

CTEST(generic_array, get_size)
{
    collection(int) list = NULL;
    ASSERT_EQUAL(0, collection_get_size(list));
}

CTEST(generic_array, get_capacity)
{
    collection(int) list = NULL;
    ASSERT_EQUAL(0, collection_get_capacity(list));
}

CTEST(generic_array, add_item)
{
    collection(int) list = NULL;
    collection_add(list, 123);
    ASSERT_EQUAL(123, list[0]);
    collection_free(list);
}

CTEST(generic_array, remove_item)
{
    collection(int) list = NULL;
    for (int i = 0; i < 10; i++)
    {
        collection_add(list, i);
    }
    collection_remove(list, 7);
    ASSERT_EQUAL(9, collection_get_size(list));
    ASSERT_EQUAL(8, list[7]);
    collection_free(list);
}

CTEST(generic_array, remove_to_start)
{
    collection(int) list = NULL;
    for (int i = 0; i < 10; i++)
    {
        collection_add(list, i);
    }
    for (int i = 9; i > -1; i--)
    {
        collection_remove(list, i);
    }
    ASSERT_EQUAL(0, collection_get_size(list));
    ASSERT_EQUAL(0, list[0]);
    collection_free(list);
}

CTEST(generic_array, copy)
{
    collection(int) list = NULL;
    for (int i = 0; i < 10; i++)
    {
        collection_add(list, i);
    }
    collection(int) list_copy = NULL;
    collection_copy(list_copy, list);
    for (int i = 0; i < collection_get_size(list); i++)
    {
        ASSERT_EQUAL(list[i], list_copy[i]);
    }
    collection_free(list);
    collection_free(list_copy);
}

CTEST(generic_array, use_case)
{
    collection(int) list_of_exps = NULL;
    for (int i = 1; i <= 1024; i *= 2)
    {
        collection_add(list_of_exps, i);
    }
    ASSERT_EQUAL(11, collection_get_size(list_of_exps));
    collection_remove(list_of_exps, 0);
    for (int i = 2, j = 0; i <= 1024; i *= 2, j++)
    {
        ASSERT_EQUAL(i, list_of_exps[j]);
    }
    collection_free(list_of_exps);
}