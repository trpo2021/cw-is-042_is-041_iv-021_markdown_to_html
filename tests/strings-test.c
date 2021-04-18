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