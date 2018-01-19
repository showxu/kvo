//
//  sel.h
//  kvo
//
//

_Pragma("once")

#include "strproc.h"
#include <stdio.h>
#include <assert.h>
#include <objc/runtime.h>

_Pragma("clang assume_nonnull begin")

static inline SEL _Nullable sel_setter(SEL sel) {
    if (!sel)
        return nil;
    __auto_type name = (char *)sel_getName(sel);
    __auto_type len = strlen(name);
    if (!len) return nil;
    strlwc(name, 0);
    char ret[len + 4];
    // O(n²)
    // strcat(strcat(strcpy(ret, "set"), name), ":");
    // O(n)
    assert(snprintf(ret, sizeof(ret), "%s%s%s", "set", name, ":") > 0);
    return sel_getUid(ret);
}

static inline SEL _Nullable sel_getter(SEL sel) {
    if (!sel)
        return nil;
    __auto_type name = (char *)sel_getName(sel);
    __auto_type len = strlen(name);
    if (len <= 0 || !strprefix(name, "set") || ! !strsuffix(name, ":")) {
        return nil;
    }
    name[len - 1] = '\0';
    name += 3;
    strlwc(name, 0);
    return sel_getUid(name);
}

_Pragma("clang assume_nonnull end")
