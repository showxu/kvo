//
//  string.h
//  kvo
//
//

_Pragma("once")

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

_Pragma("clang assume_nonnull begin")

static inline char* strmap(char *str, char (^body)(char)) {
    __auto_type len = strlen(str);
    __auto_type ret = (char *)malloc(sizeof(str));
    strcpy(ret, str);
    for (__auto_type i = 0; i < len; i ++) {
         ret[i] = body(str[i]);
    }
    return ret;
}

static inline void strupc(char *str) __attribute__((overloadable)) {
    while ((*str = toupper(*str))) str ++;
}

static inline void strupc(char *str, int at)  __attribute__((overloadable)) {
    __auto_type len = strlen(str);
    __auto_type idx = 0;
    if (idx > len) return;
    
    while (idx != at) {
        idx ++;
        str ++;
    }
    *str = toupper(*str);
}

static inline void strlwc(char *str) __attribute__((overloadable)) {
    while ((*str = tolower(*str))) str ++;
}

static inline void strlwc(char *str, int at)  __attribute__((overloadable)) {
    __auto_type len = strlen(str);
    __auto_type idx = 0;
    if (idx > len) return;
    
    while (idx != at) {
        idx ++;
        str ++;
    }
    *str = tolower(*str);
}

static inline bool strprefix(const char *str, const char *prefix) {
    if (!str || !prefix) return false;
    __auto_type pos = strstr(str, prefix);
    return *str == *pos;
}

static inline bool strsuffix(char *str, char *suffix) {
    if (!str || !suffix)
        return false;
    __auto_type str_len = strlen(str);
    __auto_type suffix_len = strlen(suffix);
    if (suffix_len > str_len)
        return false;
    return strncmp(str + str_len - suffix_len, suffix, suffix_len) == 0;
}

_Pragma("clang assume_nonnull end")
