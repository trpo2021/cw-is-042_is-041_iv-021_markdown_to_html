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