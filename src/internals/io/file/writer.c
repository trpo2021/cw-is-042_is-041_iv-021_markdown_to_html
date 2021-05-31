#include <internals/exceptions/exceptions.h>
#include <internals/io/file/writer.h>
#include <stdio.h>
#include <string.h>

void write_file(const char* file_path, const char* content)
{
    FILE* output = fopen(file_path, "w");
    if (!output)
    {
        throw_exception(ExceptionFileNotFound, file_path);
    }
    fwrite(content, sizeof(char), strlen(content), output);
    fclose(output);
}