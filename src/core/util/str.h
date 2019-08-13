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
unsigned int str_length(char* src);
void str_sub_string(str_t* src, unsigned int start, unsigned int end);

#endif // STR_H
