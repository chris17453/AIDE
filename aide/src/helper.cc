#include "helper.h"


clock_t start;

void profileStart(){
     start = clock() ;
}
   
double profileEnd(){
    clock_t end = clock() ;
    return (end-start)/(double)CLOCKS_PER_SEC ;
}



char *strtoupper(char *str){
    int i = 0;
    char *p = (char*) malloc((strlen(str) + 1) * sizeof(char));
    for(; str[i] != '\0'; ++i){
        if((str[i] >= 'a') && (str[i] <= 'z'))
            p[i] = str[i] + 'A' - 'a';
        else
            p[i] = str[i];
    }
    p[i] = '\0';
    return p;
}

char *strtolower(char *str){
    int i = 0;
    char *p = (char*) malloc((strlen(str) + 1) * sizeof(char));

    for(; str[i] != '\0'; ++i){
        if((str[i] >= 'A') && (str[i] <= 'Z'))
            p[i] = tolower(str[i]);
        else
            p[i] = str[i];
    }
    p[i] = '\0';
    return p;
}

void error_exit(const char *msg){
  fprintf(stderr, "%s\n", msg);
  printf( "%s\n", msg);
  //exit(1);
}

char *string_duplicate(const char *str){
  char *new_str = strdup(str);
  if(new_str == NULL)
    error_exit("strdup failed, exiting.");
  return new_str;
}

void *memcpy2(void* dest, const void* src, size_t count)
{
    char* dst8 = (char*)dest;
    char* src8 = (char*)src;

    if (count & 1) {
        dst8[0] = src8[0];
        dst8 += 1;
        src8 += 1;
    }

    count /= 2;
    while (count--) {
        dst8[0] = src8[0];
        dst8[1] = src8[1];

        dst8 += 2;
        src8 += 2;
    }
    return dest;
}
