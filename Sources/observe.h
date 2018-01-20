//
//  observe.h
//  kvo
//
//

_Pragma("once")

_Pragma("clang diagnostic push")
_Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"")
#include <objc/hashtable2.h>
_Pragma("clang diagnostic push")

typedef void(^Callback)(id value);

void observe(id observable, const char *key, Callback will, Callback did);
