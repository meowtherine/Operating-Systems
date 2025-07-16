#ifndef STRING_H
#define STRING_H

int strcmp(const char *s1, const char *s2);
char *strcpy(char *dest, const char *src);
int strlen(const char *s);
char *strcat(char *dest, const char *src);
char *strchr(const char *s, int c);
char *strtok(char *str, const char *delim);

#endif
