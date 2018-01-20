//
//  sel.h
//  kvo
//
//

_Pragma("once")

#include <objc/runtime.h>

_Pragma("clang assume_nonnull begin")

SEL _Nullable sel_setter(SEL sel);
SEL _Nullable sel_getter(SEL sel);

_Pragma("clang assume_nonnull end")
