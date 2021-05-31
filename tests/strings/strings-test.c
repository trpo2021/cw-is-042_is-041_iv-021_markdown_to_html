#include <ctest.h>
#include <internals/memext/memext.h>
#include <internals/strings/strings.h>
#include <stdio.h>

CTEST(strings, init)
{
    String* s = sinit(10);
    ASSERT_NOT_NULL(s);
    sfree(s);
}

CTEST(strings, length)
{
    String* s = sinit(10);
    ASSERT_EQUAL(0, slength(s));
    sfree(s);
}

CTEST(strings, capacity)
{
    String* s = sinit(10);
    ASSERT_EQUAL(10, scapacity(s));
    sfree(s);
}

CTEST(strings, print)
{
    String* s = sinit(10);
    ASSERT_STR("\0", sraw(s));
    sfree(s);
}

CTEST(strings, create)
{
    String* s = screate("test");
    ASSERT_STR("test", sraw(s));
    sfree(s);
}

CTEST(strings, create_empty)
{
    String* s = screate("");
    ASSERT_STR("\0", sraw(s));
    sfree(s);
}

CTEST(strings, create_length)
{
    String* s = screate("test");
    ASSERT_EQUAL(4, slength(s));
    sfree(s);
}

CTEST(strings, create_capacity)
{
    String* s = screate("test");
    ASSERT_EQUAL(4 + 10, scapacity(s));
    sfree(s);
}

CTEST(strings, create_empty_length)
{
    String* s = screate("");
    ASSERT_EQUAL(0, slength(s));
    sfree(s);
}

CTEST(strings, create_empty_capacity)
{
    String* s = screate("");
    ASSERT_EQUAL(10, scapacity(s));
    sfree(s);
}

CTEST(strings, copy)
{
    String* s = screate("test");
    String* s2 = scopy(s);
    ASSERT_STR(sraw(s2), sraw(s));
    sfree(s);
    sfree(s2);
}

CTEST(strings, copy_length)
{
    String* s = screate("test");
    String* s2 = scopy(s);
    ASSERT_EQUAL(slength(s2), slength(s));
    sfree(s);
    sfree(s2);
}

CTEST(strings, copy_capacity)
{
    String* s = screate("test");
    String* s2 = scopy(s);
    ASSERT_EQUAL(scapacity(s2), scapacity(s));
    sfree(s);
    sfree(s2);
}

CTEST(strings, copy_empty)
{
    String* s = screate("");
    String* s2 = scopy(s);
    ASSERT_EQUAL(scapacity(s2), scapacity(s));
    sfree(s);
    sfree(s2);
}

CTEST(strings, copy_empty_length)
{
    String* s = screate("");
    String* s2 = scopy(s);
    ASSERT_EQUAL(scapacity(s2), scapacity(s));
    sfree(s);
    sfree(s2);
}

CTEST(strings, copy_empty_capacity)
{
    String* s = screate("");
    String* s2 = scopy(s);
    ASSERT_EQUAL(scapacity(s2), scapacity(s));
    sfree(s);
    sfree(s2);
}

CTEST(strings, set)
{
    String* s = screate("test");
    sset(s, 2, 'w');
    ASSERT_STR("tewt", sraw(s));
    sfree(s);
}

CTEST(strings, set_out_of_range)
{
    String* s = screate("test");
    sset(s, 222, 'w');
    ASSERT_STR("test", sraw(s));
    sfree(s);
}

CTEST(strings, get)
{
    String* s = screate("test");
    ASSERT_EQUAL('t', sget(s, 0));
    ASSERT_EQUAL('e', sget(s, 1));
    ASSERT_EQUAL('s', sget(s, 2));
    ASSERT_EQUAL('t', sget(s, 3));
    sfree(s);
}

CTEST(strings, get_out_of_range)
{
    String* s = screate("test");
    ASSERT_EQUAL(-1, sget(s, 7));
    sfree(s);
}

CTEST(strings, append)
{
    String* s = screate("test");
    sappend(s, '2');
    ASSERT_STR("test2", sraw(s));
    sfree(s);
}

CTEST(strings, append_realloc)
{
    String* s = screate("test");
    for (size_t i = '0'; i < '0' + 20; i++)
    {
        sappend(s, (char)i);
    }
    ASSERT_STR("test0123456789:;<=>?@ABC", sraw(s));
    sfree(s);
}

CTEST(strings, append_empty)
{
    String* s = screate("");
    sappend(s, 'w');
    ASSERT_STR("w", sraw(s));
    sfree(s);
}

CTEST(strings, append_empty_realloc)
{
    String* s = screate("");
    for (size_t i = '0'; i < '0' + 20; i++)
    {
        sappend(s, (char)i);
    }
    ASSERT_STR("0123456789:;<=>?@ABC", sraw(s));
    sfree(s);
}

CTEST(strings, concat)
{
    String* s = screate("test");
    sconcat(s, " concated");
    ASSERT_STR("test concated", sraw(s));
    sfree(s);
}

CTEST(strings, concat_empty)
{
    String* s = screate("");
    sconcat(s, "concated");
    ASSERT_STR("concated", sraw(s));
    sfree(s);
}

CTEST(strings, contains)
{
    String* s = screate("test");
    ASSERT_TRUE(scontains(s, "t"));
    ASSERT_TRUE(scontains(s, "e"));
    ASSERT_TRUE(scontains(s, "st"));
    sfree(s);
}

CTEST(strings, contains_false)
{
    String* s = screate("test");
    ASSERT_FALSE(scontains(s, "str"));
    sfree(s);
}

CTEST(strings, empty_contains_true)
{
    String* s = screate("");
    ASSERT_TRUE(scontains(s, ""));
    sfree(s);
}

CTEST(strings, empty_contains_false)
{
    String* s = screate("");
    ASSERT_FALSE(scontains(s, "test"));
    sfree(s);
}

CTEST(strings, compare_true)
{
    String* s = screate("test");
    ASSERT_TRUE(scompare(s, "test"));
    sfree(s);
}

CTEST(strings, compare_false)
{
    String* s = screate("test");
    ASSERT_FALSE(scompare(s, "str"));
    sfree(s);
}

CTEST(strings, compare_empty_true)
{
    String* s = screate("");
    ASSERT_TRUE(scompare(s, ""));
    sfree(s);
}

CTEST(strings, compare_empty_false)
{
    String* s = screate("");
    ASSERT_FALSE(scompare(s, "str"));
    sfree(s);
}

CTEST(strings, replace)
{
    String* s = screate("test test  test  spaces!");
    String* replaced = sreplace(s, "", " ");
    sfree(s);
    ASSERT_STR("testtesttestspaces!", sraw(replaced));
    sfree(replaced);
}

CTEST(strings, replace_not_contains)
{
    String* s = screate("test test  test  spaces!");
    String* replaced = sreplace(s, "not", "");
    ASSERT_STR(sraw(s), sraw(replaced));
    sfree(s);
    sfree(replaced);
}

CTEST(strings, replace_empty_old)
{
    String* s = screate("test test  test  spaces!");
    String* replaced = sreplace(s, "", "");
    ASSERT_STR(sraw(s), sraw(replaced));
    sfree(s);
    sfree(replaced);
}

CTEST(strings, replace_empty_source)
{
    String* s = screate("test test  test  spaces!");
    String* replaced = sreplace(NULL, "", "");
    ASSERT_NULL(replaced);
    sfree(s);
}

CTEST(strings, replace_empty_new)
{
    String* s = screate("test test  test  spaces!");
    String* replaced = sreplace(s, "", "test");
    ASSERT_STR("     spaces!", sraw(replaced));
    sfree(s);
    sfree(replaced);
}

CTEST(strings, empty_string_replace)
{
    String* s = screate("");
    String* replaced = sreplace(s, "test", "ssss");
    ASSERT_STR(sraw(s), sraw(replaced));
    sfree(s);
    sfree(replaced);
}

CTEST(strings, replace_large_substr_len)
{
    String* s = screate("test");
    String* replaced = sreplace(s, "wwww", "t");
    ASSERT_STR("wwwweswwww", sraw(replaced));
    sfree(s);
    sfree(replaced);
}

CTEST(strings, replace_tabs_with_spaces)
{
    String* s = screate("\t\ttest ");
    String* replaced = sreplace(s, "    ", "\t");
    ASSERT_STR("        test ", sraw(replaced));
    sfree(s);
    sfree(replaced);
}

CTEST(strings, split)
{
    String* s = screate("Share Improve this answer Follow");
    size_t len = 0;
    String** container = ssplit(s, " ", &len);
    ASSERT_STR("Share", sraw(container[0]));
    ASSERT_STR("Improve", sraw(container[1]));
    ASSERT_STR("this", sraw(container[2]));
    ASSERT_STR("answer", sraw(container[3]));
    ASSERT_STR("Follow", sraw(container[4]));
    sfree(s);
    for (int i = 0; i < len; i++)
    {
        sfree(container[i]);
    }
    free(container);
}

CTEST(strings, split_empty_pattern)
{
    String* s = screate("Share Improve this answer Follow");
    size_t len = 0;
    String** container = ssplit(s, "6", &len);
    ASSERT_STR("Share Improve this answer Follow", sraw(*container));
    sfree(s);
    sfree(container[0]);
    free(container);
}

CTEST(strings, split_empty_string)
{
    String* s = screate("");
    size_t len = 0;
    String** container = ssplit(s, "test", &len);
    ASSERT_NULL(container);
    sfree(s);
}

CTEST(strings, split_save_source)
{
    String* s = screate("Share Improve this answer Follow");
    size_t len = 0;
    String** container = ssplit(s, " ", &len);
    for (int i = 0; i < len; i++)
    {
        sfree(container[i]);
    }
    free(container);
    ASSERT_STR("Share Improve this answer Follow", sraw(s));
    sfree(s);
}

CTEST(strings, insert_start)
{
    String* s = screate("test");
    sinsert(s, "2", 0);
    ASSERT_STR("2test", sraw(s));
    sfree(s);
}

CTEST(strings, insert_mid)
{
    String* s = screate("test");
    sinsert(s, "2", 2);
    ASSERT_STR("te2st", sraw(s));
    sfree(s);
}

CTEST(strings, insert_end)
{
    String* s = screate("test");
    sinsert(s, "2", slength(s) - 1);
    ASSERT_STR("tes2t", sraw(s));
    sfree(s);
}

CTEST(strings, insert_realloc)
{
    String* s = screate("test");
    sinsert(s, "1234567890qwertyuiop", slength(s) / 2);
    ASSERT_STR("te1234567890qwertyuiopst", sraw(s));
    sfree(s);
}

CTEST(strings, insert_empty)
{
    String* s = screate("test");
    sinsert(s, "", 2);
    ASSERT_STR("test", sraw(s));
    sfree(s);
}

CTEST(strings, insert_in_empty_string)
{
    String* s = screate("");
    sinsert(s, "test", 0);
    ASSERT_STR("test", sraw(s));
    sfree(s);
}

CTEST(strings, insert_out_of_range)
{
    String* s = screate("test");
    sinsert(s, " test", 10);
    ASSERT_STR("test", sraw(s));
    sfree(s);
}

CTEST(strings, to_string)
{
    int data_int = -123;
    float data_float = -0.876;
    double data_double = 123.456;
    char data_char = 't';
    char data_hex = 0x90;
    char* str = NULL;
    int len = 0;
    convert_to_char_array(str, data_int, "%d", len);
    ASSERT_STR("-123", str);
    free(str);
    convert_to_char_array(str, data_float, "%g", len);
    ASSERT_STR("-0.876", str);
    free(str);
    convert_to_char_array(str, data_double, "%g", len);
    ASSERT_STR("123.456", str);
    free(str);
    convert_to_char_array(str, data_char, "%c", len);
    ASSERT_STR("t", str);
    free(str);
    convert_to_char_array(str, data_hex, "%hhx", len);
    ASSERT_STR("90", str);
    free(str);
}

CTEST(strings, clear)
{
    String* s = screate("test");
    sclear(s);
    ASSERT_STR("\0", sraw(s));
    sfree(s);
}