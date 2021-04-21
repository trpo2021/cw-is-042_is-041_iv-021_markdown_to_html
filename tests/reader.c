#include <../src/internals/io/reader.h>
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

    char* buf = malloc(sizeof(char) * file_size);
    fread(buf, sizeof(char), file_size, input);
    fclose(input);

    return buf;
}