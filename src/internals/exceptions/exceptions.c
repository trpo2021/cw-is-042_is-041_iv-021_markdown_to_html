#include <internals/exceptions/exceptions.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    ExceptionCount = 7,
    ExceptionInfoCount = 2

} ExceptionsConstants;

static const char* EXCEPTION_INFO[ExceptionCount][ExceptionInfoCount] = {
    [ExceptionFileNotFound] = {"FileNotFound", "Could not open file -"},
    [ExceptionNullPointer] = {"NullPointer", "Pointer was NULL -"},
    [ExceptionIndexOutOfRange] = {"IndexOutOfRange", "Index was out of range -"},
    [ExceptionOutOfMemory] = {"OutOfMemory", "Could not allocate enough memory -"},
    [ExceptionStdinCharacterLimit] = {"StdinCharacterLimit", "You have reached stdin character limit."},
    [ExceptionUnknownArg] = {"UnknownArgument", "You entered an unknown argument."}};

void throw_exception(TypeOfException ex, const char* msg)
{
    fprintf(stderr, "\n\033[31mException\033[0m: %s.\n", EXCEPTION_INFO[ex][0]);
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