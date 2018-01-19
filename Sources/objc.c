//
//  objc.c
//  kvo
//
//

#include "objc.h"
#include <stdlib.h>

static inline Class _class_impl_stub(id self, SEL _cmd) {
    return class_getSuperclass(object_getClass(self));
}

struct objc_super object_getSuper(id object) {
    __auto_type cls = class_getSuperclass(object_getClass(object));
    return (struct objc_super) {
        .receiver = object,
#if !defined(__cplusplus)  &&  !__OBJC2__
        .class = cls
#else
        .super_class = cls
#endif
        /* super_class is the first class to search */
    };
}

Class _Nullable
objc_createObservableClass(Class _Nonnull super, const char * _Nonnull name,
                           size_t extraBytes) {
    // objc_duplicateClass(Class  _Nonnull __unsafe_unretained original, const char * _Nonnull name, size_t extraBytes)
    __auto_type observable = objc_getClass(name);
    if (observable) return observable;
    
    const __auto_type sel = sel_getUid("class");
    observable = objc_allocateClassPair(super, name, 0);
    __auto_type method = class_getClassMethod(super, sel);
    
    if (observable != nil && method != nil) {
        class_addMethod(object_getClass((id)observable),
                        sel,
                        (IMP)_class_impl_stub,
                        method_getTypeEncoding(method));
        objc_registerClassPair(observable);
        return observable;
    }
    return nil;
}

bool class_contains(Class class, SEL name) __attribute__((overloadable)) {
    __auto_type count = (unsigned int)0;
    __auto_type flag = false;

    const __auto_type list = class_copyMethodList(class, &count);
    if (!list) return flag;

    for (__auto_type i = 0; i < count; i+= 1) {
        const __auto_type sel = method_getName(list[i]);
        if (sel_isEqual(sel, name)) {
            flag = true;
            goto cleanup;
        }
    }
cleanup:
    free(list);
    return flag;
}
