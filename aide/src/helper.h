#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>




void profileStart();
double profileEnd();
char *strtoupper(char *str);
char *strtolower(char *str);
void error_exit(const char *msg);
char *string_duplicate(const char *str);
char *string_duplicate_and_caseadjust(const char *str);
void *memcpy2(void*,const void*,size_t);
