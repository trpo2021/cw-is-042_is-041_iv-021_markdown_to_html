#include <../src/internals/strings/strings.h>
#include <ctest.h>
#include <stdio.h>

CTEST(strings, init)
{
    string s = init(10);
    ASSERT_NOT_NULL(s);
}

CTEST(strings, length)
{
    string s = init(10);
    ASSERT_EQUAL(0, s->Length(s));
}

CTEST(strings, capacity)
{
    string s = init(10);
    ASSERT_EQUAL(10, s->Capacity(s));
}

CTEST(strings, print)
{
    string s = init(10);
    ASSERT_STR("\0", s->Text(s));
}

CTEST(strings, print_content)
{
    string s = create("test");
    printf("%s", s->Text(s));
}

CTEST(strings, create)
{
    string s = create("test");
    ASSERT_STR("test", s->Text(s));
}

CTEST(strings, create_empty)
{
    string s = create("");
    ASSERT_STR("\0", s->Text(s));
}

CTEST(strings, create_length)
{
    string s = create("test");
    ASSERT_EQUAL(4, s->Length(s));
}

CTEST(strings, create_capacity)
{
    string s = create("test");
    ASSERT_EQUAL(4 + 10, s->Capacity(s));
}

CTEST(strings, create_empty_length)
{
    string s = create("");
    ASSERT_EQUAL(0, s->Length(s));
}

CTEST(strings, create_empty_capacity)
{
    string s = create("");
    ASSERT_EQUAL(10, s->Capacity(s));
}

CTEST(strings, copy)
{
    string s = create("test");
    string s2 = s->Copy(s);
    ASSERT_STR(s2->Text(s2), s->Text(s));
}

CTEST(strings, copy_length)
{
    string s = create("test");
    string s2 = s->Copy(s);
    ASSERT_EQUAL(s2->Length(s2), s->Length(s));
}

CTEST(strings, copy_capacity)
{
    string s = create("test");
    string s2 = s->Copy(s);
    ASSERT_EQUAL(s2->Capacity(s2), s->Capacity(s));
}

CTEST(strings, copy_empty)
{
    string s = create("");
    string s2 = s->Copy(s);
    ASSERT_EQUAL(s2->Capacity(s2), s->Capacity(s));
}

CTEST(strings, copy_empty_length)
{
    string s = create("");
    string s2 = s->Copy(s);
    ASSERT_EQUAL(s2->Capacity(s2), s->Capacity(s));
}

CTEST(strings, copy_empty_capacity)
{
    string s = create("");
    string s2 = s->Copy(s);
    ASSERT_EQUAL(s2->Capacity(s2), s->Capacity(s));
}

CTEST(strings, free_string)
{
    string s = create("test");
    s->Free(s);
    ASSERT_NULL(s->internals);
}

CTEST(strings, free_empty_string)
{
    string s = create("");
    s->Free(s);
    ASSERT_NULL(s->internals);
}

CTEST(strings, set)
{
    string s = create("test");
    s->Set(s, 2, 'w');
    ASSERT_STR("tewt", s->Text(s));
}

CTEST(strings, set_out_of_range)
{
    string s = create("test");
    s->Set(s, 222, 'w');
    ASSERT_STR("test", s->Text(s));
}

CTEST(strings, get)
{
    string s = create("test");
    ASSERT_EQUAL('t', s->Get(s, 0));
    ASSERT_EQUAL('e', s->Get(s, 1));
    ASSERT_EQUAL('s', s->Get(s, 2));
    ASSERT_EQUAL('t', s->Get(s, 3));
}

CTEST(strings, get_out_of_range)
{
    string s = create("test");
    ASSERT_EQUAL(-1, s->Get(s, 7));
}

CTEST(strings, append)
{
    string s = create("test");
    s->Append(s, '2');
    ASSERT_STR("test2", s->Text(s));
}

CTEST(strings, append_realloc)
{
    string s = create("test");
    for (size_t i = '0'; i < '0' + 20; i++)
    {
        s->Append(s, (char)i);
    }
    ASSERT_STR("test0123456789:;<=>?@ABC", s->Text(s));
}

CTEST(strings, append_empty)
{
    string s = create("");
    s->Append(s, 'w');
    ASSERT_STR("w", s->Text(s));
}

CTEST(strings, append_empty_realloc)
{
    string s = create("");
    for (size_t i = '0'; i < '0' + 20; i++)
    {
        s->Append(s, (char)i);
    }
    ASSERT_STR("0123456789:;<=>?@ABC", s->Text(s));
}

CTEST(strings, concat)
{
    string s = create("test");
    s->Concat(s, " concated");
    ASSERT_STR("test concated", s->Text(s));
}

CTEST(strings, concat_empty)
{
    string s = create("");
    s->Concat(s, "concated");
    ASSERT_STR("concated", s->Text(s));
}

CTEST(strings, contains)
{
    string s = create("test");
    ASSERT_TRUE(s->Contains(s, "t"));
    ASSERT_TRUE(s->Contains(s, "e"));
    ASSERT_TRUE(s->Contains(s, "st"));
}

CTEST(strings, contains_false)
{
    string s = create("test");
    ASSERT_FALSE(s->Contains(s, "str"));
}

CTEST(strings, empty_contains_true)
{
    string s = create("");
    ASSERT_TRUE(s->Contains(s, ""));
}

CTEST(strings, empty_contains_false)
{
    string s = create("");
    ASSERT_FALSE(s->Contains(s, "test"));
}

CTEST(strings, compare_true)
{
    string s = create("test");
    ASSERT_TRUE(s->Compare(s, "test"));
}

CTEST(strings, compare_false)
{
    string s = create("test");
    ASSERT_FALSE(s->Compare(s, "str"));
}

CTEST(strings, compare_empty_true)
{
    string s = create("");
    ASSERT_TRUE(s->Compare(s, ""));
}

CTEST(strings, compare_empty_false)
{
    string s = create("");
    ASSERT_FALSE(s->Compare(s, "str"));
}

CTEST(strings, replace)
{
    string s = create("test test  test  spaces!");
    string replaced = s->Replace(s, " ", "");
    s->Free(s);
    ASSERT_STR("testtesttestspaces!", replaced->Text(replaced));
}

CTEST(strings, replace_not_contains)
{
    string s = create("test test  test  spaces!");
    string replaced = s->Replace(s, "not", "");
    ASSERT_STR(s->Text(s), replaced->Text(replaced));
}

CTEST(strings, replace_empty_old)
{
    string s = create("test test  test  spaces!");
    string replaced = s->Replace(s, "", "");
    ASSERT_NULL(replaced);
}

CTEST(strings, replace_empty_source)
{
    string s = create("test test  test  spaces!");
    string replaced = s->Replace(NULL, "", "");
    ASSERT_NULL(replaced);
}

CTEST(strings, replace_empty_new)
{
    string s = create("test test  test  spaces!");
    string replaced = s->Replace(s, "test", "");
    ASSERT_STR("     spaces!", replaced->Text(replaced));
}

CTEST(strings, empty_string_replace)
{
    string s = create("");
    string replaced = s->Replace(s, "test", "ssss");
    ASSERT_NULL(replaced);
}

CTEST(strings, replace_large_substr_len)
{
    string s = create("test");
    string replaced = s->Replace(s, "tested", "wwww");
    ASSERT_STR(s->Text(s), replaced->Text(replaced));
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
}

CTEST(strings, split_empty_pattern)
{
    string s = create("Share Improve this answer Follow");
    size_t len = 0;
    string* container = s->Split(s, "6", &len);
    ASSERT_STR("Share Improve this answer Follow", (*container)->Text(*container));
}

CTEST(strings, split_empty_string)
{
    string s = create("");
    size_t len = 0;
    ASSERT_NULL(s->Split(s, "test", &len));
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
    ASSERT_STR("Share Improve this answer Follow", s->Text(s));
}