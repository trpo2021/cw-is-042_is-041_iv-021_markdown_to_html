#pragma once

typedef enum
{
    ExceptionFileNotFound = 1,
    ExceptionNullPointer,
    ExceptionIndexOutOfRange,
    ExceptionOutOfMemory,
    ExceptionStdinCharacterLimit,
    ExceptionUnknownArg
} TypeOfException;

void throw_exception(TypeOfException ex, const char* msg);