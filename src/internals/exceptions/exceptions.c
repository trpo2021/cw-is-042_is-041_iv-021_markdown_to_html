#include <internals/exceptions/exceptions.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    ExceptionCount = 4
} ExceptionsConstants;

static const char* EXCEPTION_INFO[][ExceptionCount] = {
    [ExceptionFileNotFound] = {"FileNotFound", "Could not open file -"},
    [ExceptionNullPointer] = {"NullPointer", "Pointer was NULL -"},
    [ExceptionIndexOutOfRange] = {"IndexOutOfRange", "Index was out of range -"},
    [ExceptionOutOfMemory] = {"OutOfMemory", "Could not allocate enough memory -"}};

void throw_exception(TypeOfException ex, const char* file_name, const int line, const char* msg)
{
    fprintf(stderr, "\033[31mException\033[0m: %s.\n", EXCEPTION_INFO[ex][0]);
    fprintf(stderr, "\033[31mLocation\033[0m: In file - %s. At line - %d.\n", file_name, line);
    fprintf(stderr, "%s: ", "\033[31mAddition information\033[0m");
    if (msg)
    {
        fprintf(stderr, "%s %s.\n", EXCEPTION_INFO[ex][1], msg);
    }
    else
    {
        fprintf(stderr, "%s.\n", "Not provided");
    }
    exit(ex);
}