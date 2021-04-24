#include <../src/internals/io/file/reader.h>
#include <stdio.h>
#include <stdlib.h>

char* read_file(const char* file_path)
{
    FILE* input = fopen(file_path, "r");

    int file_size;
    fseek(input, 0L, SEEK_END);
    file_size = ftell(input);
    fseek(input, 0L, SEEK_SET);
    rewind(input);

    char* buf = malloc(file_size + 1);
    fread(buf, 1, file_size, input);
    buf[file_size] = '\0';
    fclose(input);

    return buf;
}