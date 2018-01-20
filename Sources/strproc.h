//
//  string.h
//  kvo
//
//

_Pragma("once")

#include <stdbool.h>
#include <string.h>

char* strmap(char *__str, char (^__body)(char));
void strupc(char *__str) __attribute__((overloadable));
void strupc(char *__str, int __at)  __attribute__((overloadable));
void strlwc(char *__str) __attribute__((overloadable));
void strlwc(char *__str, int __at)  __attribute__((overloadable));
bool strpre(const char *__str, const char *__prefix);
bool strsuf(char *__str, char *__suffix);
