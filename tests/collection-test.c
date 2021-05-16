#include <ctest.h>
#include <internals/parser/collection.h>
#include <stdio.h>

CTEST(generic_array, get_size)
{
    Array(int) list = NULL;
    ASSERT_EQUAL(0, get_array_length(list));
}

CTEST(generic_array, get_capacity)
{
    Array(int) list = NULL;
    ASSERT_EQUAL(0, get_array_capacity(list));
}

CTEST(generic_array, add_item)
{
    Array(int) list = NULL;
    add_array_item(list, 123);
    ASSERT_EQUAL(123, list[0]);
    free_array(list);
}

CTEST(generic_array, remove_item)
{
    Array(int) list = NULL;
    for (int i = 0; i < 10; i++)
    {
        add_array_item(list, i);
    }
    remove_array_item(list, 7);
    ASSERT_EQUAL(9, get_array_length(list));
    ASSERT_EQUAL(8, list[7]);
    free_array(list);
}

CTEST(generic_array, remove_to_start)
{
    Array(int) list = NULL;
    for (int i = 0; i < 10; i++)
    {
        add_array_item(list, i);
    }
    for (int i = 9; i > -1; i--)
    {
        remove_array_item(list, i);
    }
    ASSERT_EQUAL(0, get_array_length(list));
    ASSERT_EQUAL(0, list[0]);
    free_array(list);
}

CTEST(generic_array, copy)
{
    Array(int) list = NULL;
    for (int i = 0; i < 10; i++)
    {
        add_array_item(list, i);
    }
    Array(int) list_copy = NULL;
    copy_array(list_copy, list);
    for (int i = 0; i < get_array_length(list); i++)
    {
        ASSERT_EQUAL(list[i], list_copy[i]);
    }
    free_array(list);
    free_array(list_copy);
}

CTEST(generic_array, use_case)
{
    Array(int) list_of_exps = NULL;
    for (int i = 1; i <= 1024; i *= 2)
    {
        add_array_item(list_of_exps, i);
    }
    ASSERT_EQUAL(11, get_array_length(list_of_exps));
    remove_array_item(list_of_exps, 0);
    for (int i = 2, j = 0; i <= 1024; i *= 2, j++)
    {
        ASSERT_EQUAL(i, list_of_exps[j]);
    }
    free_array(list_of_exps);
}