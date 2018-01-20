//
//  hashtable2_algrithm.h
//  kvo
//
//

_Pragma("once")

#include <stdio.h>

_Pragma("clang diagnostic push")
_Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"")
#include <objc/hashtable2.h>
_Pragma("clang diagnostic push")

void foreach(NXHashTable * _Nonnull table, void (^ _Nullable body)(id _Nullable));
