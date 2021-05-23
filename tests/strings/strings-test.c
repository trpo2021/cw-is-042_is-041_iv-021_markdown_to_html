#include <ctest.h>
#include <internals/strings/strings.h>
#include <stdio.h>

CTEST(strings, init)
{
    String* s = init_string(10);
    ASSERT_NOT_NULL(s);
    s->free(s);
}

CTEST(strings, length)
{
    String* s = init_string(10);
    ASSERT_EQUAL(0, s->length(s));
    s->free(s);
}

CTEST(strings, capacity)
{
    String* s = init_string(10);
    ASSERT_EQUAL(10, s->capacity(s));
    s->free(s);
}

CTEST(strings, print)
{
    String* s = init_string(10);
    ASSERT_STR("\0", s->text(s));
    s->free(s);
}

CTEST(strings, print_content)
{
    String* s = create_string("test");
    printf("%s", s->text(s));
    s->free(s);
}

CTEST(strings, create)
{
    String* s = create_string("test");
    ASSERT_STR("test", s->text(s));
    s->free(s);
}

CTEST(strings, create_empty)
{
    String* s = create_string("");
    ASSERT_STR("\0", s->text(s));
    s->free(s);
}

CTEST(strings, create_length)
{
    String* s = create_string("test");
    ASSERT_EQUAL(4, s->length(s));
    s->free(s);
}

CTEST(strings, create_capacity)
{
    String* s = create_string("test");
    ASSERT_EQUAL(4 + 10, s->capacity(s));
    s->free(s);
}

CTEST(strings, create_empty_length)
{
    String* s = create_string("");
    ASSERT_EQUAL(0, s->length(s));
    s->free(s);
}

CTEST(strings, create_empty_capacity)
{
    String* s = create_string("");
    ASSERT_EQUAL(10, s->capacity(s));
    s->free(s);
}

CTEST(strings, copy)
{
    String* s = create_string("test");
    String* s2 = s->copy(s);
    ASSERT_STR(s2->text(s2), s->text(s));
    s->free(s);
    s2->free(s2);
}

CTEST(strings, copy_length)
{
    String* s = create_string("test");
    String* s2 = s->copy(s);
    ASSERT_EQUAL(s2->length(s2), s->length(s));
    s->free(s);
    s2->free(s2);
}

CTEST(strings, copy_capacity)
{
    String* s = create_string("test");
    String* s2 = s->copy(s);
    ASSERT_EQUAL(s2->capacity(s2), s->capacity(s));
    s->free(s);
    s2->free(s2);
}

CTEST(strings, copy_empty)
{
    String* s = create_string("");
    String* s2 = s->copy(s);
    ASSERT_EQUAL(s2->capacity(s2), s->capacity(s));
    s->free(s);
    s2->free(s2);
}

CTEST(strings, copy_empty_length)
{
    String* s = create_string("");
    String* s2 = s->copy(s);
    ASSERT_EQUAL(s2->capacity(s2), s->capacity(s));
    s->free(s);
    s2->free(s2);
}

CTEST(strings, copy_empty_capacity)
{
    String* s = create_string("");
    String* s2 = s->copy(s);
    ASSERT_EQUAL(s2->capacity(s2), s->capacity(s));
    s->free(s);
    s2->free(s2);
}

CTEST(strings, set)
{
    String* s = create_string("test");
    s->set(s, 2, 'w');
    ASSERT_STR("tewt", s->text(s));
    s->free(s);
}

CTEST(strings, set_out_of_range)
{
    String* s = create_string("test");
    s->set(s, 222, 'w');
    ASSERT_STR("test", s->text(s));
    s->free(s);
}

CTEST(strings, get)
{
    String* s = create_string("test");
    ASSERT_EQUAL('t', s->get(s, 0));
    ASSERT_EQUAL('e', s->get(s, 1));
    ASSERT_EQUAL('s', s->get(s, 2));
    ASSERT_EQUAL('t', s->get(s, 3));
    s->free(s);
}

CTEST(strings, get_out_of_range)
{
    String* s = create_string("test");
    ASSERT_EQUAL(-1, s->get(s, 7));
    s->free(s);
}

CTEST(strings, append)
{
    String* s = create_string("test");
    s->append(s, '2');
    ASSERT_STR("test2", s->text(s));
    s->free(s);
}

CTEST(strings, append_realloc)
{
    String* s = create_string("test");
    for (size_t i = '0'; i < '0' + 20; i++)
    {
        s->append(s, (char)i);
    }
    ASSERT_STR("test0123456789:;<=>?@ABC", s->text(s));
    s->free(s);
}

CTEST(strings, append_empty)
{
    String* s = create_string("");
    s->append(s, 'w');
    ASSERT_STR("w", s->text(s));
    s->free(s);
}

CTEST(strings, append_empty_realloc)
{
    String* s = create_string("");
    for (size_t i = '0'; i < '0' + 20; i++)
    {
        s->append(s, (char)i);
    }
    ASSERT_STR("0123456789:;<=>?@ABC", s->text(s));
    s->free(s);
}

CTEST(strings, concat)
{
    String* s = create_string("test");
    s->concat(s, " concated");
    ASSERT_STR("test concated", s->text(s));
    s->free(s);
}

CTEST(strings, concat_empty)
{
    String* s = create_string("");
    s->concat(s, "concated");
    ASSERT_STR("concated", s->text(s));
    s->free(s);
}

CTEST(strings, contains)
{
    String* s = create_string("test");
    ASSERT_TRUE(s->contains(s, "t"));
    ASSERT_TRUE(s->contains(s, "e"));
    ASSERT_TRUE(s->contains(s, "st"));
    s->free(s);
}

CTEST(strings, contains_false)
{
    String* s = create_string("test");
    ASSERT_FALSE(s->contains(s, "str"));
    s->free(s);
}

CTEST(strings, empty_contains_true)
{
    String* s = create_string("");
    ASSERT_TRUE(s->contains(s, ""));
    s->free(s);
}

CTEST(strings, empty_contains_false)
{
    String* s = create_string("");
    ASSERT_FALSE(s->contains(s, "test"));
    s->free(s);
}

CTEST(strings, compare_true)
{
    String* s = create_string("test");
    ASSERT_TRUE(s->compare(s, "test"));
    s->free(s);
}

CTEST(strings, compare_false)
{
    String* s = create_string("test");
    ASSERT_FALSE(s->compare(s, "str"));
    s->free(s);
}

CTEST(strings, compare_empty_true)
{
    String* s = create_string("");
    ASSERT_TRUE(s->compare(s, ""));
    s->free(s);
}

CTEST(strings, compare_empty_false)
{
    String* s = create_string("");
    ASSERT_FALSE(s->compare(s, "str"));
    s->free(s);
}

CTEST(strings, replace)
{
    String* s = create_string("test test  test  spaces!");
    String* replaced = s->replace(s, " ", "");
    s->free(s);
    ASSERT_STR("testtesttestspaces!", replaced->text(replaced));
    replaced->free(replaced);
}

CTEST(strings, replace_not_contains)
{
    String* s = create_string("test test  test  spaces!");
    String* replaced = s->replace(s, "not", "");
    ASSERT_STR(s->text(s), replaced->text(replaced));
    s->free(s);
    replaced->free(replaced);
}

CTEST(strings, replace_empty_old)
{
    String* s = create_string("test test  test  spaces!");
    String* replaced = s->replace(s, "", "");
    ASSERT_STR(s->text(s), replaced->text(replaced));
    s->free(s);
    replaced->free(replaced);
}

CTEST(strings, replace_empty_source)
{
    String* s = create_string("test test  test  spaces!");
    String* replaced = s->replace(NULL, "", "");
    ASSERT_NULL(replaced);
    s->free(s);
}

CTEST(strings, replace_empty_new)
{
    String* s = create_string("test test  test  spaces!");
    String* replaced = s->replace(s, "test", "");
    ASSERT_STR("     spaces!", replaced->text(replaced));
    s->free(s);
    replaced->free(replaced);
}

CTEST(strings, empty_string_replace)
{
    String* s = create_string("");
    String* replaced = s->replace(s, "test", "ssss");
    ASSERT_STR(s->text(s), replaced->text(replaced));
    s->free(s);
    replaced->free(replaced);
}

CTEST(strings, replace_large_substr_len)
{
    String* s = create_string("test");
    String* replaced = s->replace(s, "t", "wwww");
    ASSERT_STR("wwwweswwww", replaced->text(replaced));
    s->free(s);
    replaced->free(replaced);
}

CTEST(strings, replace_tabs_with_spaces)
{
    String* s = create_string("\t\ttest ");
    String* replaced = s->replace(s, "\t", "    ");
    ASSERT_STR("        test ", replaced->text(replaced));
    s->free(s);
    replaced->free(replaced);
}

CTEST(strings, split)
{
    String* s = create_string("Share Improve this answer Follow");
    size_t len = 0;
    String** container = s->split(s, " ", &len);
    ASSERT_STR("Share", container[0]->text(container[0]));
    ASSERT_STR("Improve", container[1]->text(container[1]));
    ASSERT_STR("this", container[2]->text(container[2]));
    ASSERT_STR("answer", container[3]->text(container[3]));
    ASSERT_STR("Follow", container[4]->text(container[4]));
    s->free(s);
    for (int i = 0; i < len; i++)
    {
        container[i]->free(container[i]);
    }
    free(container);
}

CTEST(strings, split_empty_pattern)
{
    String* s = create_string("Share Improve this answer Follow");
    size_t len = 0;
    String** container = s->split(s, "6", &len);
    ASSERT_STR("Share Improve this answer Follow", (*container)->text(*container));
    s->free(s);
    (container[0])->free(container[0]);
    free(container);
}

CTEST(strings, split_empty_string)
{
    String* s = create_string("");
    size_t len = 0;
    String** container = s->split(s, "test", &len);
    ASSERT_NULL(container);
    s->free(s);
}

CTEST(strings, split_save_source)
{
    String* s = create_string("Share Improve this answer Follow");
    size_t len = 0;
    String** container = s->split(s, " ", &len);
    for (int i = 0; i < len; i++)
    {
        container[i]->free(container[i]);
    }
    free(container);
    ASSERT_STR("Share Improve this answer Follow", s->text(s));
    s->free(s);
}

CTEST(strings, insert_start)
{
    String* s = create_string("test");
    s->insert(s, "2", 0);
    ASSERT_STR("2test", s->text(s));
    s->free(s);
}

CTEST(strings, insert_mid)
{
    String* s = create_string("test");
    s->insert(s, "2", 2);
    ASSERT_STR("te2st", s->text(s));
    s->free(s);
}

CTEST(strings, insert_end)
{
    String* s = create_string("test");
    s->insert(s, "2", s->length(s) - 1);
    ASSERT_STR("tes2t", s->text(s));
    s->free(s);
}

CTEST(strings, insert_realloc)
{
    String* s = create_string("test");
    s->insert(s, "1234567890qwertyuiop", s->length(s) / 2);
    ASSERT_STR("te1234567890qwertyuiopst", s->text(s));
    s->free(s);
}

CTEST(strings, insert_empty)
{
    String* s = create_string("test");
    s->insert(s, "", 2);
    ASSERT_STR("test", s->text(s));
    s->free(s);
}

CTEST(strings, insert_in_empty_string)
{
    String* s = create_string("");
    s->insert(s, "test", 0);
    ASSERT_STR("test", s->text(s));
    s->free(s);
}

CTEST(strings, insert_out_of_range)
{
    String* s = create_string("test");
    s->insert(s, " test", 10);
    ASSERT_STR("test", s->text(s));
    s->free(s);
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
    String* s = create_string("test");
    s->clear(s);
    ASSERT_STR("\0", s->text(s));
    s->free(s);
}