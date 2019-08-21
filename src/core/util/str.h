#ifndef STR_H
#define STR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct str_t {
    unsigned int length;
    char* data;
} str_t;

str_t str_new(char src[]);
void str_del(str_t* str);
void str_print(str_t* str);
unsigned int str_length(char* src);
void str_sub_string(str_t* src, unsigned int start, unsigned int end);
void str_concat(str_t* dest, str_t* src);

#endif // STR_H
