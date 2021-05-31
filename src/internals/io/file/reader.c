#include <internals/exceptions/exceptions.h>
#include <internals/io/file/reader.h>
#include <internals/memext/memext.h>
#include <stdio.h>

static size_t get_file_size(FILE* file)
{
    size_t size;
    fseek(file, 0L, SEEK_END);
    size = ftell(file);
    fseek(file, 0L, SEEK_SET);
    rewind(file);
    return size;
}

static char* get_file_content(FILE* file, size_t size)
{
    char* content = mem_alloc(size + 1);
    fread(content, sizeof(char), size, file);
    content[size] = 0;
    fclose(file);
    return content;
}

char* read_file(const char* file_path)
{
    FILE* input = fopen(file_path, "r");
    if (!input)
    {
        throw_exception(ExceptionFileNotFound, file_path);
    }
    return get_file_content(input, get_file_size(input));
}