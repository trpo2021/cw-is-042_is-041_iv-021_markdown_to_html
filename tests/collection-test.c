#include <ctest.h>
#include <internals/parser/collection.h>
#include <stdio.h>

CTEST(generic_array, get_size)
{
    ArrayList(int) list = NULL;
    ASSERT_EQUAL(0, ArrayListGetLength(list));
}

CTEST(generic_array, get_capacity)
{
    ArrayList(int) list = NULL;
    ASSERT_EQUAL(0, ArrayListGetCapacity(list));
}

CTEST(generic_array, add_item)
{
    ArrayList(int) list = NULL;
    ArrayListAdd(list, 123);
    ASSERT_EQUAL(123, list[0]);
    ArrayListFree(list);
}

CTEST(generic_array, remove_item)
{
    ArrayList(int) list = NULL;
    for (int i = 0; i < 10; i++)
    {
        ArrayListAdd(list, i);
    }
    ArrayListRemove(list, 7);
    ASSERT_EQUAL(9, ArrayListGetLength(list));
    ASSERT_EQUAL(8, list[7]);
    ArrayListFree(list);
}

CTEST(generic_array, remove_to_start)
{
    ArrayList(int) list = NULL;
    for (int i = 0; i < 10; i++)
    {
        ArrayListAdd(list, i);
    }
    for (int i = 9; i > -1; i--)
    {
        ArrayListRemove(list, i);
    }
    ASSERT_EQUAL(0, ArrayListGetLength(list));
    ASSERT_EQUAL(0, list[0]);
    ArrayListFree(list);
}

CTEST(generic_array, copy)
{
    ArrayList(int) list = NULL;
    for (int i = 0; i < 10; i++)
    {
        ArrayListAdd(list, i);
    }
    ArrayList(int) list_copy = NULL;
    ArrayListCopy(list_copy, list);
    for (int i = 0; i < ArrayListGetLength(list); i++)
    {
        ASSERT_EQUAL(list[i], list_copy[i]);
    }
    ArrayListFree(list);
    ArrayListFree(list_copy);
}

CTEST(generic_array, use_case)
{
    ArrayList(int) list_of_exps = NULL;
    for (int i = 1; i <= 1024; i *= 2)
    {
        ArrayListAdd(list_of_exps, i);
    }
    ASSERT_EQUAL(11, ArrayListGetLength(list_of_exps));
    ArrayListRemove(list_of_exps, 0);
    for (int i = 2, j = 0; i <= 1024; i *= 2, j++)
    {
        ASSERT_EQUAL(i, list_of_exps[j]);
    }
    ArrayListFree(list_of_exps);
}