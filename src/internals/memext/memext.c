#include <internals/exceptions/exceptions.h>
#include <internals/memext/memext.h>

void* mem_alloc(size_t block_size)
{
    void* block_ptr = malloc(block_size);
    if (!block_ptr)
    {
        throw_exception(ExceptionOutOfMemory, "malloc");
    }
    return block_ptr;
}

void* mem_calloc(size_t count, size_t elem_size)
{
    void* block_ptr = calloc(count, elem_size);
    if (!block_ptr)
    {
        throw_exception(ExceptionOutOfMemory, "calloc");
    }
    return block_ptr;
}

void* mem_realloc(void* block, size_t size)
{
    void* block_ptr = realloc(block, size);
    if (!block_ptr)
    {
        throw_exception(ExceptionOutOfMemory, "realloc");
    }
    return block_ptr;
}

void mem_free(void* block)
{
    if (block)
    {
        free(block);
    }
}