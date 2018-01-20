//
//  objc_core.h
//  kvo
//
//

_Pragma("once")

#include <objc/message.h>
#include <stdbool.h>

_Pragma("clang assume_nonnull begin")

extern struct objc_super
    object_getSuper(id object);

extern Class _Nullable
    objc_createObservableClass(Class _Nonnull super, const char * _Nonnull name, size_t extraBytes);

extern bool
    class_contains(Class class, SEL name) __attribute__((overloadable));

_Pragma("clang assume_nonnull end")
