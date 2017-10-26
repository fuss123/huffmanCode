#ifndef STRING_FUNC_H
#define STRING_FUNC_H

#include <stdio.h>
#include <stdlib.h>

typedef enum { FALSE = 0, TRUE } boolean;

int myStringLength(char *string);
boolean myStringCompare(char *first, char *second);
void myStringCopy(char *target, char *source);
void myStringCat(char *original, char *add);
char *myStringCat_returnNewStringVer(char *orignal, char *add);

#endif
