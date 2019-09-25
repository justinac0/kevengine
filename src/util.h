#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// memory allocation debugging.
void* u_malloc(size_t size, uint32_t line, char* file);
void* u_calloc(size_t itemCount, size_t size, uint32_t line, char* file);
void* u_realloc(void* ptr, size_t size, uint32_t line, char* file);
void u_free(void* ptr, uint32_t line, char* file);

#ifdef U_MEM_DEBUG
    #warning Memory debugging enabled...

    #define malloc(size)            u_malloc(size, __LINE__, __FILE__);
    #define calloc(itemCount, size) u_calloc(itemCount, size, __LINE__, __FILE__);
    #define realloc(ptr, size)      u_realloc(ptr, size, __LINE__, __FILE__);
    #define free(ptr)               u_free(ptr, __LINE__, __FILE__);
#endif

// static sized lists.
typedef struct {
    uint32_t    length;
    uint32_t    capacity;
    int*        items;
} u_int_list_t;

u_int_list_t u_int_list_new(uint32_t capacity);
void u_int_list_add(u_int_list_t* list, int item);

typedef struct {
    uint32_t    length;
    uint32_t    capacity;
    char*       items;
} u_float_list_t;

u_float_list_t u_float_list_new(uint32_t capacity);
void u_float_list_add(u_float_list_t* list, float item);

void u_list_delete(void* ptr);

// file I/O.
#define U_FILE_READ_FAIL "READ_FAIL"
#define U_FILE_BUFFER_MEMORY_FAIL "MEMORY_FAIL"

char* u_file_read(char* fileLocation);

#endif // UTIL_H
