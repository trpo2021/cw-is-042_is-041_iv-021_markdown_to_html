#include <../src/internals/io/std/reader.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// end of input
static const char* const BREAK_LINE = "-quit\n";

int stdin_read(char* buf)
{
    for (;;)
    {
        char* line = malloc(STDIN_LIMIT);
        fgets(line, STDIN_LIMIT, stdin);
        // if this string equals "-quit", close input
        if (strcmp(line, BREAK_LINE) == 0)
        {
            free(line);
            return STDIN_EXIT_CODE;
        }
        // if line fits into result, concat it
        else if (strlen(buf) + strlen(line) < STDIN_LIMIT)
        {
            strcat(buf, line);
            free(line);
        }
        else
        {
            puts("\n\tYou have reached character limit.");
            puts("\n\tTo convert more than 1000 characters, you can use file.");
            puts("\n\tRun './converter --help' for more information.\n");
            free(line);
            return STDIN_LIMIT_RECHEAD_CODE;
        }
    }
}