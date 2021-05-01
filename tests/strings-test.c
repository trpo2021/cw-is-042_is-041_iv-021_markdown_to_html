#include <ctest.h>
#include <internals/strings/strings.h>
#include <stdio.h>

CTEST(strings, init)
{
    string s = init(10);
    ASSERT_NOT_NULL(s);
    s->Free(s);
}

CTEST(strings, length)
{
    string s = init(10);
    ASSERT_EQUAL(0, s->Length(s));
    s->Free(s);
}

CTEST(strings, capacity)
{
    string s = init(10);
    ASSERT_EQUAL(10, s->Capacity(s));
    s->Free(s);
}

CTEST(strings, print)
{
    string s = init(10);
    ASSERT_STR("\0", s->Text(s));
    s->Free(s);
}

CTEST(strings, print_content)
{
    string s = create("test");
    printf("%s", s->Text(s));
    s->Free(s);
}

CTEST(strings, create)
{
    string s = create("test");
    ASSERT_STR("test", s->Text(s));
    s->Free(s);
}

CTEST(strings, create_empty)
{
    string s = create("");
    ASSERT_STR("\0", s->Text(s));
    s->Free(s);
}

CTEST(strings, create_length)
{
    string s = create("test");
    ASSERT_EQUAL(4, s->Length(s));
    s->Free(s);
}

CTEST(strings, create_capacity)
{
    string s = create("test");
    ASSERT_EQUAL(4 + 10, s->Capacity(s));
    s->Free(s);
}

CTEST(strings, create_empty_length)
{
    string s = create("");
    ASSERT_EQUAL(0, s->Length(s));
    s->Free(s);
}

CTEST(strings, create_empty_capacity)
{
    string s = create("");
    ASSERT_EQUAL(10, s->Capacity(s));
    s->Free(s);
}

CTEST(strings, copy)
{
    string s = create("test");
    string s2 = s->Copy(s);
    ASSERT_STR(s2->Text(s2), s->Text(s));
    s->Free(s);
    s2->Free(s2);
}

CTEST(strings, copy_length)
{
    string s = create("test");
    string s2 = s->Copy(s);
    ASSERT_EQUAL(s2->Length(s2), s->Length(s));
    s->Free(s);
    s2->Free(s2);
}

CTEST(strings, copy_capacity)
{
    string s = create("test");
    string s2 = s->Copy(s);
    ASSERT_EQUAL(s2->Capacity(s2), s->Capacity(s));
    s->Free(s);
    s2->Free(s2);
}

CTEST(strings, copy_empty)
{
    string s = create("");
    string s2 = s->Copy(s);
    ASSERT_EQUAL(s2->Capacity(s2), s->Capacity(s));
    s->Free(s);
    s2->Free(s2);
}

CTEST(strings, copy_empty_length)
{
    string s = create("");
    string s2 = s->Copy(s);
    ASSERT_EQUAL(s2->Capacity(s2), s->Capacity(s));
    s->Free(s);
    s2->Free(s2);
}

CTEST(strings, copy_empty_capacity)
{
    string s = create("");
    string s2 = s->Copy(s);
    ASSERT_EQUAL(s2->Capacity(s2), s->Capacity(s));
    s->Free(s);
    s2->Free(s2);
}

CTEST(strings, set)
{
    string s = create("test");
    s->Set(s, 2, 'w');
    ASSERT_STR("tewt", s->Text(s));
    s->Free(s);
}

CTEST(strings, set_out_of_range)
{
    string s = create("test");
    s->Set(s, 222, 'w');
    ASSERT_STR("test", s->Text(s));
    s->Free(s);
}

CTEST(strings, get)
{
    string s = create("test");
    ASSERT_EQUAL('t', s->Get(s, 0));
    ASSERT_EQUAL('e', s->Get(s, 1));
    ASSERT_EQUAL('s', s->Get(s, 2));
    ASSERT_EQUAL('t', s->Get(s, 3));
    s->Free(s);
}

CTEST(strings, get_out_of_range)
{
    string s = create("test");
    ASSERT_EQUAL(-1, s->Get(s, 7));
    s->Free(s);
}

CTEST(strings, append)
{
    string s = create("test");
    s->Append(s, '2');
    ASSERT_STR("test2", s->Text(s));
    s->Free(s);
}

CTEST(strings, append_realloc)
{
    string s = create("test");
    for (size_t i = '0'; i < '0' + 20; i++)
    {
        s->Append(s, (char)i);
    }
    ASSERT_STR("test0123456789:;<=>?@ABC", s->Text(s));
    s->Free(s);
}

CTEST(strings, append_empty)
{
    string s = create("");
    s->Append(s, 'w');
    ASSERT_STR("w", s->Text(s));
    s->Free(s);
}

CTEST(strings, append_empty_realloc)
{
    string s = create("");
    for (size_t i = '0'; i < '0' + 20; i++)
    {
        s->Append(s, (char)i);
    }
    ASSERT_STR("0123456789:;<=>?@ABC", s->Text(s));
    s->Free(s);
}

CTEST(strings, concat)
{
    string s = create("test");
    s->Concat(s, " concated");
    ASSERT_STR("test concated", s->Text(s));
    s->Free(s);
}

CTEST(strings, concat_empty)
{
    string s = create("");
    s->Concat(s, "concated");
    ASSERT_STR("concated", s->Text(s));
    s->Free(s);
}

CTEST(strings, contains)
{
    string s = create("test");
    ASSERT_TRUE(s->Contains(s, "t"));
    ASSERT_TRUE(s->Contains(s, "e"));
    ASSERT_TRUE(s->Contains(s, "st"));
    s->Free(s);
}

CTEST(strings, contains_false)
{
    string s = create("test");
    ASSERT_FALSE(s->Contains(s, "str"));
    s->Free(s);
}

CTEST(strings, empty_contains_true)
{
    string s = create("");
    ASSERT_TRUE(s->Contains(s, ""));
    s->Free(s);
}

CTEST(strings, empty_contains_false)
{
    string s = create("");
    ASSERT_FALSE(s->Contains(s, "test"));
    s->Free(s);
}

CTEST(strings, compare_true)
{
    string s = create("test");
    ASSERT_TRUE(s->Compare(s, "test"));
    s->Free(s);
}

CTEST(strings, compare_false)
{
    string s = create("test");
    ASSERT_FALSE(s->Compare(s, "str"));
    s->Free(s);
}

CTEST(strings, compare_empty_true)
{
    string s = create("");
    ASSERT_TRUE(s->Compare(s, ""));
    s->Free(s);
}

CTEST(strings, compare_empty_false)
{
    string s = create("");
    ASSERT_FALSE(s->Compare(s, "str"));
    s->Free(s);
}

CTEST(strings, replace)
{
    string s = create("test test  test  spaces!");
    string replaced = s->Replace(s, " ", "");
    s->Free(s);
    ASSERT_STR("testtesttestspaces!", replaced->Text(replaced));
    replaced->Free(replaced);
}

CTEST(strings, replace_not_contains)
{
    string s = create("test test  test  spaces!");
    string replaced = s->Replace(s, "not", "");
    ASSERT_STR(s->Text(s), replaced->Text(replaced));
    s->Free(s);
    replaced->Free(replaced);
}

CTEST(strings, replace_empty_old)
{
    string s = create("test test  test  spaces!");
    string replaced = s->Replace(s, "", "");
    ASSERT_NULL(replaced);
    s->Free(s);
}

CTEST(strings, replace_empty_source)
{
    string s = create("test test  test  spaces!");
    string replaced = s->Replace(NULL, "", "");
    ASSERT_NULL(replaced);
    s->Free(s);
}

CTEST(strings, replace_empty_new)
{
    string s = create("test test  test  spaces!");
    string replaced = s->Replace(s, "test", "");
    ASSERT_STR("     spaces!", replaced->Text(replaced));
    s->Free(s);
    replaced->Free(replaced);
}

CTEST(strings, empty_string_replace)
{
    string s = create("");
    string replaced = s->Replace(s, "test", "ssss");
    ASSERT_NULL(replaced);
    s->Free(s);
}

CTEST(strings, replace_large_substr_len)
{
    string s = create("test");
    string replaced = s->Replace(s, "tested", "wwww");
    ASSERT_STR(s->Text(s), replaced->Text(replaced));
    s->Free(s);
    replaced->Free(replaced);
}

CTEST(strings, split)
{
    string s = create("Share Improve this answer Follow");
    size_t len = 0;
    string* container = s->Split(s, " ", &len);
    ASSERT_STR("Share", container[0]->Text(container[0]));
    ASSERT_STR("Improve", container[1]->Text(container[1]));
    ASSERT_STR("this", container[2]->Text(container[2]));
    ASSERT_STR("answer", container[3]->Text(container[3]));
    ASSERT_STR("Follow", container[4]->Text(container[4]));
    s->Free(s);
    for (int i = 0; i < len; i++)
    {
        container[i]->Free(container[i]);
    }
    free(container);
}

CTEST(strings, split_empty_pattern)
{
    string s = create("Share Improve this answer Follow");
    size_t len = 0;
    string* container = s->Split(s, "6", &len);
    ASSERT_STR("Share Improve this answer Follow", (*container)->Text(*container));
    s->Free(s);
    (container[0])->Free(container[0]);
    free(container);
}

CTEST(strings, split_empty_string)
{
    string s = create("");
    size_t len = 0;
    string* container = s->Split(s, "test", &len);
    ASSERT_NULL(container);
    s->Free(s);
}

CTEST(strings, split_save_source)
{
    string s = create("Share Improve this answer Follow");
    size_t len = 0;
    string* container = s->Split(s, " ", &len);
    for (int i = 0; i < len; i++)
    {
        container[i]->Free(container[i]);
    }
    free(container);
    ASSERT_STR("Share Improve this answer Follow", s->Text(s));
    s->Free(s);
}

CTEST(strings, insert_start)
{
    string s = create("test");
    s->Insert(s, "2", 0);
    ASSERT_STR("2test", s->Text(s));
    s->Free(s);
}

CTEST(strings, insert_mid)
{
    string s = create("test");
    s->Insert(s, "2", 2);
    ASSERT_STR("te2st", s->Text(s));
    s->Free(s);
}

CTEST(strings, insert_end)
{
    string s = create("test");
    s->Insert(s, "2", s->Length(s) - 1);
    ASSERT_STR("tes2t", s->Text(s));
    s->Free(s);
}

CTEST(strings, insert_realloc)
{
    string s = create("test");
    s->Insert(s, "1234567890qwertyuiop", s->Length(s) / 2);
    ASSERT_STR("te1234567890qwertyuiopst", s->Text(s));
    s->Free(s);
}

CTEST(strings, insert_empty)
{
    string s = create("test");
    s->Insert(s, "", 2);
    ASSERT_STR("test", s->Text(s));
    s->Free(s);
}

CTEST(strings, insert_in_empty_string)
{
    string s = create("");
    s->Insert(s, "test", 0);
    ASSERT_STR("test", s->Text(s));
    s->Free(s);
}

CTEST(strings, insert_out_of_range)
{
    string s = create("test");
    s->Insert(s, " test", 10);
    ASSERT_STR("test", s->Text(s));
    s->Free(s);
}

CTEST(strings, to_string)
{
    int data_int = -123;
    float data_float = -0.876;
    double data_double = 123.456;
    char data_char = 't';
    char data_hex = 0x90;
    char* str = NULL;
    int len;
    ToCharArray(str, data_int, "%d", len);
    ASSERT_STR("-123", str);
    free(str);
    ToCharArray(str, data_float, "%g", len);
    ASSERT_STR("-0.876", str);
    free(str);
    ToCharArray(str, data_double, "%g", len);
    ASSERT_STR("123.456", str);
    free(str);
    ToCharArray(str, data_char, "%c", len);
    ASSERT_STR("t", str);
    free(str);
    ToCharArray(str, data_hex, "%hhx", len);
    ASSERT_STR("90", str);
    free(str);
}

CTEST(strings, clear)
{
    string s = create("test");
    s->Clear(s);
    ASSERT_STR("\0", s->Text(s));
    s->Free(s);
}