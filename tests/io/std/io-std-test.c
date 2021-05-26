#include <ctest.h>
#include <internals/io/std/reader.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CTEST(io_std, read)
{
    const char* input_data = "first line\nsecond line\n-quit\n";
    FILE* fp = fopen("stdin-test.txt", "w");
    fwrite(input_data, 1, strlen(input_data), fp);
    fclose(fp);

    fp = freopen("stdin-test.txt", "r", stdin);
    const char* expected = "first line\nsecond line\n";
    char* received_data = read_stdin();
    ASSERT_STR(expected, received_data);
    free(received_data);
    fclose(fp);
    remove("stdin-test.txt");
}

CTEST(io_std, read_more_than_limit)
{
    char data[10000];
    memset(data, '1', 9999);
    data[9999] = 0;
    FILE* fp = fopen("stdin-test.txt", "w");
    fwrite(data, 1, strlen(data), fp);
    fclose(fp);

    fp = freopen("stdin-test.txt", "r", stdin);
    read_stdin();
    fclose(fp);
    remove("stdin-test.txt");
}