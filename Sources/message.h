//
//  msg.h
//  KVO.swift
//
//

_Pragma("once")

#include <stdio.h>
#include <objc/message.h>

_Pragma("clang assume_nonnull begin")

static inline void object_msgSendSuper(struct objc_super *super, SEL _cmd, id newValue) {
    ((void (*)(void *, SEL, id))objc_msgSendSuper)(&super, _cmd, newValue);
}

static inline struct objc_super object_getSuper(id self) {
    struct objc_super super = {
        .receiver = self,
        .super_class = class_getSuperclass(object_getClass(self))
    };
    return super;
}

OBJC_EXPORT Class
objc_createObservableClass(Class _Nonnull cls, const char * _Nonnull name,
                                  size_t extraBytes)
    OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0, 2.0);

_Pragma("clang assume_nonnull end")

