#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

void* dmem_malloc(size_t size, int line, const char* file);
void dmem_free(void* ptr, int line, const char* file);

#define malloc(size)    dmem_malloc(size, __LINE__, __FILE__)
#define free(ptr)       dmem_free(ptr, __LINE__, __FILE__)

typedef struct list_fixed_t {
    unsigned int    length;
    unsigned int    dataTypeSize;
    void*           data;
} list_fixed_t;

list_fixed_t list_fixed_create(unsigned int dataTypeSize, unsigned int length);
void list_fixed_free(list_fixed_t* list);

#endif // LIST_H
