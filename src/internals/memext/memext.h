#pragma once

#include <stdlib.h>

void* mem_alloc(size_t block_size);
void* mem_calloc(size_t count, size_t elem_size);
void* mem_realloc(void* block, size_t size);
void mem_free(void* block);