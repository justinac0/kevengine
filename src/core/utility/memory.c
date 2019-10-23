#include "memory.h"

void* u_malloc(size_t size, uint32_t line, const char* file, const char* func) {
    void* memory = malloc(size);
    
    if (memory == NULL) {
        fprintf(stderr, "[FAILED] -- MALLOC::(%p)(Line: %d, File: %s, Function: %s)", line, file, func);
        exit(EXIT_FAILURE);
    }

    printf("[SUCCESS] -- MALLOC::(%p)(Line: %d, File: %s, Function: %s)\n", memory, line, file, func);

    return memory;
}

void* u_calloc(size_t itemCount, size_t size, uint32_t line, const char* file, const char* func) {
    void* memory = calloc(itemCount, size);
    
    if (memory == NULL) {
        fprintf(stderr, "[FAILED] -- CALLOC::(%p)(Line: %d, File: %s, Function: %s)", line, file, func);
        exit(EXIT_FAILURE);
    }

    printf("[SUCCESS] -- CALLOC::(%p)(Line: %d, File: %s, Function: %s)\n", memory, line, file, func);

    return memory;
}

void* u_realloc(void* ptr, size_t size, uint32_t line, const char* file, const char* func) {
    void* memory = realloc(ptr, size);

    if (memory == NULL) {
        fprintf(stderr, "[FAILED] -- REALLOC::(%p)(Line: %d, File: %s, Function: %s)", line, file, func);
        exit(EXIT_FAILURE);
    }

    printf("[SUCCESS] -- REALLOC::(%p)(Line: %d, File: %s, Function: %s)\n", memory, line, file, func);

    return memory;
}

void u_free(void* ptr, uint32_t line, const char* file, const char* func) {
    free(ptr);
    printf("[SUCCESS] -- FREE::(%p)(Line: %d, File: %s, Function: %s)\n", ptr, line, file, func);
    ptr = NULL;
}

memory_pool_t memory_pool_create(uint32_t capacity) {
    memory_pool_t mp;
    mp.size     = 0;
    mp.capacity = capacity;
    mp.length   = 0;
    mp.blocks   = (memory_block_t*) malloc(mp.capacity);

    return mp;
}

void memory_pool_destroy(memory_pool_t* mp) {
    free(mp->blocks);

    mp->size     = 0;
    mp->capacity = 0;
    mp->length   = 0;
    mp->blocks   = NULL;
}

void memory_pool_add(memory_pool_t* mp, char tag, uint32_t size, void* data) {
    if (mp->size + size >= mp->capacity) {
        printf("Memory pool is full...\n");
        return;
    }

    size_t blockSize = size + (sizeof(memory_block_t) - sizeof(void*));

    mp->blocks[mp->length].tag  = tag;
    mp->blocks[mp->length].size = blockSize;
    memcpy(&mp->blocks[mp->length].data, &data, blockSize);

    printf("::NEW_BLOCK(addr(%p) | size = %d bytes)\n", &mp->blocks[mp->length], blockSize);
    
    mp->size += blockSize;
    mp->length++;
}

void memory_pool_del(memory_pool_t* mp, uint32_t index) {
    mp->blocks[index].tag = MEMORY_BLOCK_TAG_FREE_NOW;
}
