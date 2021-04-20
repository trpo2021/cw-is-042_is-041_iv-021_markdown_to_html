#include <internals/read_and_write_file/read_write_file.h>

char* read_file(const char* file_in)
{
    FILE* input = fopen(file_in, "r");

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

FILE* create_out_file(const char* file_in)
{
    FILE* output = fopen(file_in, "w");
    return output;
}