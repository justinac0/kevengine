#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "../../../deps/glad/glad.h"

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

// file I/O.
/* read raw text file and return contents in string form */
char* u_file_read(char* fileLocation);

#endif // UTIL_H
