#pragma once

typedef enum
{
    ExceptionFileNotFound = 1,
    ExceptionNullPointer,
    ExceptionIndexOutOfRange,
    ExceptionOutOfMemory,
} TypeOfException;

void throw_exception(TypeOfException ex, const char* file_name, const int line, const char* msg);