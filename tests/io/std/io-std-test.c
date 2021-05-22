#include <ctest.h>
#include <internals/io/std/reader.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CTEST(io_std, read)
{
    /* emulate user input */

    const char* data = "first line\nsecond line\n-quit\n";
    FILE* fp = fopen("stdin-test.txt", "w");
    fwrite(data, 1, strlen(data), fp);
    fclose(fp);

    // using file as stdin
    fp = freopen("stdin-test.txt", "r", stdin);
    const char* expected = "first line\nsecond line\n";
    char* buf = calloc(STDIN_LIMIT, 1);
    stdin_read(buf);
    ASSERT_STR(expected, buf);
    free(buf);
    fclose(fp);
    remove("stdin-test.txt");
}

CTEST(io_std, read_more_than_limit)
{
    /* emulate user input */

    char* data = malloc(10000);
    for (size_t i = 0; i < 9999; ++i)
    {
        data[i] = '1';
    }
    data[9999] = '\0';
    FILE* fp = fopen("stdin-test.txt", "w");
    fwrite(data, 1, strlen(data), fp);
    free(data);
    fclose(fp);

    // using file as stdin
    fp = freopen("stdin-test.txt", "r", stdin);
    char* buf = calloc(STDIN_LIMIT, 1);
    ASSERT_EQUAL(STDIN_LIMIT_RECHEAD_CODE, stdin_read(buf));
    free(buf);
    fclose(fp);
    remove("stdin-test.txt");
}