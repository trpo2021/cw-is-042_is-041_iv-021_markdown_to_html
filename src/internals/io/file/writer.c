#include <internals/io/file/writer.h>
#include <stdio.h>
#include <string.h>

void write_file(const char* file_path, const char* content)
{
    FILE* output = fopen(file_path, "w");
    fwrite(content, sizeof(char), strlen(content), output);
    fclose(output);
}