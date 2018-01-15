//
//  message.cpp
//  KVO.swift
//
//

#import "message.h"

#import <objc/message.h>
#import <objc/runtime.h>

static inline Class __class__(id self, SEL _cmd) {
    return class_getSuperclass(object_getClass(self));
}

Class
objc_createObservableClass(Class _Nonnull cls, const char * _Nonnull name,
                                         size_t extraBytes) {
    // objc_duplicateClass(Class  _Nonnull __unsafe_unretained original, const char * _Nonnull name, size_t extraBytes)
    if (auto aCls = objc_getClass(name)) {
        return aCls;
    }
    auto sel = sel_getUid("class");
    // [if statement](http://en.cppreference.com/w/cpp/language/if )
    // [-std=c++17 (-std=c++1z in Clang 4 and earlier).](http://clang.llvm.org/cxx_status.html#cxx17 ).
    if (auto newCls = objc_allocateClassPair(cls, name, 0); auto clsMethod = class_getClassMethod(cls, sel)) {
        class_addMethod(object_getClass(newCls), sel, (IMP)__class__, method_getTypeEncoding(clsMethod));
        objc_registerClassPair(newCls);
        return newCls;
    }
    return nil;
}

