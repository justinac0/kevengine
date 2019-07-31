#include "mem.h"

void* mem_debug_malloc(size_t size, int line, const char* file) {
    void* buffer = malloc(size);

    if (!buffer) {
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }

    printf("::MALLOC::(%s)->[Line %d]\n", file, line);

    return buffer;
}

void mem_debug_free(void* ptr, int line, const char* file) {
    free(ptr);

    printf("::FREE::(%s)->[Line %d]\n", file, line);
}

mem_list_t mem_list_alloc(unsigned int dataTypeSize, unsigned int length) {
    mem_list_t list;
    list.dataTypeSize      = dataTypeSize;
    list.length            = length;
    list.data              = malloc(dataTypeSize * length);
    if (!list.data) {
        fprintf(stderr, "Failed to allocated memory.\n");
        exit(EXIT_FAILURE);
    }

    printf("(%p) Create new fixed list of length %d\n", list.data, list.length);

    return list;
}

void mem_list_free(mem_list_t* list) {
    list->dataTypeSize  = 0;
    list->length        = 0;
    printf("(%p) Free fixed list\n", list->data);

    free(list->data);
}

void mem_list_set(mem_list_t* list, void* item, unsigned int index) {
    // (list->data[index]) = item;
}
