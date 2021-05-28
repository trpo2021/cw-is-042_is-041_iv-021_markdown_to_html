#include <internals/exceptions/exceptions.h>
#include <internals/io/std/reader.h>
#include <internals/memext/memext.h>
#include <stdio.h>
#include <string.h>

typedef enum
{
    StdinCharacterLimit = 1000
} StdReaderConstants;

char* read_stdin()
{
    char* stdin_data = mem_calloc(StdinCharacterLimit + 1, sizeof(char));
    for (;;)
    {
        char* line = mem_alloc(StdinCharacterLimit + 1);
        fgets(line, StdinCharacterLimit, stdin);
        if (strcmp(line, "-quit\n") == 0)
        {
            mem_free(line);
            return stdin_data;
        }
        if (strlen(stdin_data) + strlen(line) < StdinCharacterLimit)
        {
            strcat(stdin_data, line);
            mem_free(line);
            continue;
        }
        mem_free(line);
        break;
    }
    mem_free(stdin_data);
    return NULL;
}