//
//  objc.c
//  KVO
//
//

#include <objc/objc.h>
#include <objc/message.h>

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
