#include <../src/internals/read_and_write_file/read_write_file.h>
#include <ctest.h>
#include <stdio.h>

CTEST(read_and_write_file, read_file_)
{
    const char* string = "Test.md";
    ASSERT_NOT_NULL(read_file(string));
}

CTEST(read_and_write_file, get_buf)
{
    const char* string = "Test.md";
    ASSERT_STR("read_file function test", read_file(string));
}

CTEST(read_and_write_file, create_file)
{
    const char* string = "test.html";
    create_out_file(string);
    FILE* out = fopen("test.html", "r");
    ASSERT_NOT_NULL(out);
    fclose(out);
}