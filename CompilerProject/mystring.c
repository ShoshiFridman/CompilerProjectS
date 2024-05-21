
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mystring.h"


//strlen מימוש של
int myStrlen(char* str) {
    char* s;
    for (s = str; *s; ++s);
    return (int)(s - str);
}

//strcpy מימוש של
char* myStrcpy(char* destination, const char* source) {
    char* ptr = destination;

    while (*source != '\0') {
        *ptr = *source;
        source++;
        ptr++;
    }

    *ptr = '\0';

    return destination;
}

//מימוש של strdup
char* my_strdup(const char* src) {
    // Get the length of the source string
    size_t len = strlen(src) + 1;

    // Allocate memory for the new string
    char* dest = (char*)malloc(len);

    // Check if memory allocation was successful
    if (dest != NULL) {
        // Copy the source string to the newly allocated memory
        strcpy(dest, src);
    }

    return dest;
}

//strcmp מימוש של  
int myStrcmp(const char* str1, const char* str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }

    return *(unsigned char*)str1 - *(unsigned char*)str2;
}

char* my_strchr(const char* s, int c) {
    while (*s != '\0') {
        if (*s == c) {
            return (char*)s;
        }
        s++;
    }

    return NULL;
}

//מימוש של strtok
char* mystrtok(char* str, const char* delim) {
    static char* next_token = NULL;
    char* token;

    if (str != NULL) {
        next_token = str;
    }

    if (next_token == NULL) {
        return NULL;
    }

    token = next_token;

    while (*token != '\0') {
        if (my_strchr(delim, *token) != NULL) {
            *token = '\0';
            next_token = token + 1;
            break;
        }
        token++;
    }

    return token;
}
