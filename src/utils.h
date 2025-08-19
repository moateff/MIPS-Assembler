#ifndef UTILS_H
#define UTILS_H

char *toLowerCase(char *str);
int my_strcasecmp(const char *s1, const char *s2);
char *removeSpaces(const char *src);
void trimSpaces(char *str);
void preprocessLine(char *line);
int lineHasInstruction(const char *line);
void printVisible(const char *s);

#endif // UTILS_H