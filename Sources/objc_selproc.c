//
//  selproc.c
//  kvo
//
//

#include "objc_selproc.h"
#include "strproc.h"
#include <stdio.h>
#include <assert.h>

SEL _Nullable sel_setter(SEL sel) {
    if (!sel)
        return nil;
    __auto_type name = (char *)sel_getName(sel);
    __auto_type len = strlen(name) + 1;
    char buf[len];
    memset(buf, '\0', (len)* sizeof(char));
    name = strncpy(buf, name, len);
    if (!len) return nil;
    strupc(name, 0);
    char ret[len + 4];
    // O(n²)
    // strcat(strcat(strcpy(ret, "set"), name), ":");
    // O(n)
    assert(snprintf(ret, sizeof(ret), "%s%s%s", "set", name, ":") > 0);
    return sel_getUid(ret);
}

SEL _Nullable sel_getter(SEL sel) {
    if (!sel)
        return nil;
    __auto_type name = (char *)sel_getName(sel);
    __auto_type len = strlen(name);
    if (len <= 0 || !strpre(name, "set") || !strsuf(name, ":")) {
        return nil;
    }
    __auto_type offset = 3;
    __auto_type buf_len = len - offset;
    char buf[buf_len];
    memset(buf, '\0', (buf_len)* sizeof(char));
    name = strncpy(buf, name += offset, len);
    name[buf_len - 1] = '\0';
    strlwc(name, 0);
    return sel_getUid(name);
}
