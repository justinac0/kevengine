#include "str.h"

str_t str_new(char* src) {
    str_t str;
    str.data    = src;
    str.length  = str_length(src);

    return str;
}

unsigned int str_length(char* src) {
    unsigned int length = 0;
    while (*src != '\0') {
        length++;
        src++;
    }

    return length;
}

// void str_copy(char* dest, char* src) {
//     while (*src != '\0') {
//         //*dest = *src;
//         printf("%c %c\n", *src, *dest);
//         dest++;
//         src++;
//     }
//     dest[0] = '\0';
// }

void str_sub_string(str_t src, unsigned int start, unsigned int end) {
    if (src.length > 0 && end <= src.length && start <= end) {
        unsigned int newLength = (end - start) + 1;
        char* newString;

        if ((newString = (char*)malloc(sizeof(char) * newLength + 1)) != NULL) {
            for (int i = 0; i < newLength; i++) {
                newString[i] = src.data[start+i];
            }
            newString[newLength] = '\0';
        } else {
            // print some error
        }

        // str_copy(src.data, newString);
        src.length  = str_length(src.data);

        printf("%s\n", src.data);


        free(newString);
    } else {
        // print some error
    }
}
