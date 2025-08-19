#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char *toLowerCase(const char *str) {
    char *loweredStr = strdup(str);
    for (int i = 0; str[i]; i++) {
        loweredStr[i] = tolower((unsigned char) str[i]);
    }
    return loweredStr;
}

int my_strcasecmp(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        unsigned char c1 = tolower((unsigned char)*s1++);
        unsigned char c2 = tolower((unsigned char)*s2++);
        if (c1 != c2) return c1 - c2;
    }
    return *s1 - *s2;
}

// Remove all spaces from a string, in-place or into a new buffer
char *removeSpaces(const char *src) {
    if (!src) return NULL;

    char *dest = malloc(strlen(src) + 1); 
    if (!dest) return NULL;

    char *start = dest;
    while (*src) {
        if (!isspace((unsigned char)*src)) {
            *dest ++ = *src;
        }
        src++;
    }
    *dest = '\0'; 
    return start; 
}

void stripComments(char *line) {
    char *comment = strchr(line, '#');
    if (comment) *comment = '\0'; 
}

void normalizeSpaces(char *line) {
    char buffer[256];  // temporary buffer
    int i = 0, j = 0;
    int spaceFlag = 0;

    while (line[i] != '\0') {
        if (isspace((unsigned char)line[i])) {
            if (!spaceFlag) {
                buffer[j++] = ' ';
                spaceFlag = 1;
            }
        } else {
            buffer[j++] = line[i];
            spaceFlag = 0;
        }
        i++;
    }
    buffer[j] = '\0';
    strcpy(line, buffer); 
}

void trimSpaces(char *str) {
    char *end;
    // Trim leading spaces
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return;

    // Trim trailing spaces 
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = '\0';
}

void preprocessLine(char *line) {
    stripComments(line);    
    // normalizeSpaces(line);  
    trimSpaces(line);   
}

int lineHasInstruction(const char *line) {
    if (strlen(line) <= 2) return 0; // skip empty lines
    const char *ptr = line;
    if (strchr(ptr, ':') && ptr[strlen(ptr)-1] == ':') return 0; // label-only line
    return 1; 
}

void printVisible(const char *s) {
    while (*s) {
        switch (*s) {
            case '\n': printf("\\n"); break;
            case '\t': printf("\\t"); break;
            case '\r': printf("\\r"); break;
            case '\0': printf("\\0"); return; // end of string
            default:   putchar(*s); break;
        }
        s++;
    }
}