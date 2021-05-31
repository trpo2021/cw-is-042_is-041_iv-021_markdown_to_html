#pragma once

typedef enum
{
    ExceptionFileNotFound,
    ExceptionParsingFailed,
    ExceptionIndexOutOfRange,
    ExceptionOutOfMemory,
    ExceptionStdinCharacterLimit,
    ExceptionUnknownArg
} TypeOfException;

void throw_exception(TypeOfException ex, const char* msg);