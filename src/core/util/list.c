#include "list.h"

void* dmem_malloc(size_t size, int line, const char* file) {
    void* buffer = malloc(size);

    if (!buffer) {
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }

    printf("::MALLOC::%d::%s\n", line, file);
}

void dmem_free(void* ptr, int line, const char* file) {
    free(ptr);

    printf("::FREE::%d::%s\n", line, file);
}

list_fixed_t list_fixed_create(unsigned int dataTypeSize, unsigned int length) {
    list_fixed_t list;
    list.dataTypeSize   = dataTypeSize;
    list.length         = length;
    list.data           = malloc(dataTypeSize * length);

    printf("Create new fixed list of length %d\n", list.length);
}

void list_fixed_free(list_fixed_t* list) {
    list->dataTypeSize  = 0;
    list->length        = 0;
    free(list->data);
}
