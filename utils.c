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

    char *dest = malloc(strlen(src) + 1); // allocate enough space
    if (!dest) return NULL; // handle memory allocation failure

    char *start = dest;
    while (*src) {
        if (!isspace((unsigned char)*src)) {
            *dest ++ = *src;
        }
        src++;
    }
    *dest = '\0'; // null-terminate
    return start; // return the new string without spaces
}

// Remove comments starting with '#'
void stripComments(char *line) {
    char *comment = strchr(line, '#');
    if (comment) *comment = '\0'; // terminate string at comment
}

// Normalize spaces and tabs in a line (in-place)
void normalizeSpaces(char *line) {
    char buffer[256];  // temporary buffer
    int i = 0, j = 0;
    int spaceFlag = 0;

    while (line[i] != '\0') {
        if (isspace((unsigned char)line[i])) {
            if (!spaceFlag) { // first space/tab after token
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
    strcpy(line, buffer); // copy back to original line
}

// Trim leading and trailing whitespace 
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

// Preprocess the line: remove extra spaces/tabs and trim
void preprocessLine(char *line) {
    stripComments(line);    // Remove comments
    // normalizeSpaces(line);  // Normalize spaces and tabs
    trimSpaces(line);   // Trim leading/trailing spaces
}

// Check if a line contains an instruction (not just a label)
int lineHasInstruction(const char *line) {
    const char *ptr = line;
    if (*ptr == '\0') return 0;        // empty line
    if (strchr(ptr, ':') && ptr[strlen(ptr)-1] == ':') return 0; // label-only line
    return 1; // contains instruction
}

// Print a string with visible control characters
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