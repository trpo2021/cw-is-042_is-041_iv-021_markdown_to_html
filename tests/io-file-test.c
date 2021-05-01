#include <ctest.h>
#include <internals/io/file/reader.h>
#include <internals/io/file/writer.h>
#include <stdio.h>
#include <stdlib.h>

CTEST(io_file, create_file)
{
    write_file("test.html", "test");
    FILE* fp = fopen("test.html", "r");
    ASSERT_NOT_NULL(fp);
    fclose(fp);
    remove("test.html");
}

CTEST(io_file, read_file)
{
    const char* expected = "test";
    write_file("test.md", expected);
    char* content = read_file("test.md");
    ASSERT_STR(expected, content);
    free(content);
    remove("test.md");
}