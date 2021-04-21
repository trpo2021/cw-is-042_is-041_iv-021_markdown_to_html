#include <../src/internals/io/reader.h>
#include <../src/internals/io/writer.h>
#include <ctest.h>
#include <stdio.h>
#include <stdlib.h>

CTEST(read_and_write_file, create_file)
{
    write_file("test.html", "test");
    FILE* fp = fopen("test.html", "r");
    ASSERT_NOT_NULL(fp);
    fclose(fp);
    remove("test.html");
}

CTEST(read_and_write_file, read_file)
{
    write_file("test.md", "read_file function test");
    FILE* fp = fopen("test.md", "r");
    char* content = read_file("test.md");
    ASSERT_STR("read_file function test", content);
    free(content);
    fclose(fp);
    remove("test.md");
}