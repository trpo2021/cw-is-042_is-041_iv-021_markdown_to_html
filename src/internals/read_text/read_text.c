#include <internals/read_text/read_text.h>

char* read_line()
{
    char* tmp_buf = malloc(100000);
    printf("Print \"-quit\" to exit input field\n");
    printf("Input data:\n");
    char* buf = malloc(100000);
    while (true)
    {
        tmp_buf = malloc(100000);
        tmp_buf = fgets(tmp_buf, 100000, stdin);
        if (strcmp("-quit\n", tmp_buf) != 0)
        {
            strcpy(buf, tmp_buf);
        }
        else
            break;
    }
    return buf;
}