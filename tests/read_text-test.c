#include <../src/internals/read_text/read_text.h>
#include <ctest.h>
#include <stdio.h>

CTEST(read_text, test_1)
{
    // Print "test" and after "-quit"
    ASSERT_STR("test\n", read_line());
}
