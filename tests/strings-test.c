#include <../src/internals/strings/strings.h>
#include <ctest.h>

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