//
//  strproc.c
//  kvo
//
//

#include "strproc.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

char* strmap(char *__str, char (^__body)(char)) {
    __auto_type len = strlen(__str);
    __auto_type ret = (char *)malloc(sizeof(__str));
    strcpy(ret, __str);
    for (__auto_type i = 0; i < len; i ++) {
        ret[i] = __body(__str[i]);
    }
    return ret;
}

void strupc(char *__str) __attribute__((overloadable)) {
    while ((*__str = toupper(*__str))) __str ++;
}

void strupc(char *__str, int __at)  __attribute__((overloadable)) {
    __auto_type len = strlen(__str);
    __auto_type idx = 0;
    if (idx > len) return;
    
    while (idx != __at) {
        idx ++;
        __str ++;
    }
    *__str = toupper(*__str);
}

void strlwc(char *__str) __attribute__((overloadable)) {
    while ((*__str = tolower(*__str))) __str ++;
}

void strlwc(char *__str, int __at)  __attribute__((overloadable)) {
    __auto_type len = strlen(__str);
    __auto_type idx = 0;
    if (idx > len) return;
    
    while (idx != __at) {
        idx ++;
        __str ++;
    }
    *__str = tolower(*__str);
}

bool strpre(const char *__str, const char *__prefix) {
    if (!__str || !__prefix) return false;
    __auto_type pos = strstr(__str, __prefix);
    return *__str == *pos;
}

bool strsuf(char *__str, char *__suffix) {
    if (!__str || !__suffix)
        return false;
    __auto_type strl = strlen(__str);
    __auto_type suffixl = strlen(__suffix);
    if (suffixl > strl)
        return false;
    return strncmp(__str + strl - suffixl, __suffix, suffixl) == 0;
}

