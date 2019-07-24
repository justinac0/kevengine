#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

void* dmem_malloc(size_t size, int line, const char* file);
void dmem_free(void* ptr, int line, const char* file);

// #define malloc(size)    dmem_malloc(size, __LINE__, __FILE__)
// #define free(ptr)       dmem_free(ptr, __LINE__, __FILE__)

typedef struct list_fixed_t {
    unsigned int    length;
    unsigned int    dataTypeSize;
    void**          data;
} list_fixed_t;

void list_fixed_create(list_fixed_t* dest, unsigned int dataTypeSize, unsigned int length);
void list_fixed_free(list_fixed_t* list);
void list_fixed_set(list_fixed_t* list, void* item, unsigned int index);

#endif // LIST_H
