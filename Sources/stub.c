//
//  stub.c
//  kvo
//
//

#include "stub.h"
#include "selproc.h"
#include "objc.h"
#include "obsv.h"
#include "obsv_private.h"
#include <objc/runtime.h>
#include <objc/message.h>
#include <objc/hashtable2.h>

void foreach(NXHashTable *table, void (^body)(id)) {
    if (!table) return;
    __auto_type count = 0;
    __auto_type buffer = nil;
    __auto_type state = NXInitHashState(table);
    while (NXNextHashState(table, &state, &buffer)) {
        !body ?: body(buffer);
        count++;
    }
}

Class _class_impl_stub(id self, SEL _cmd) {
    return class_getSuperclass(object_getClass(self));
}

void _setter_impl_stub(id self, SEL _cmd, id newValue) {
    __auto_type getter = sel_getter(_cmd);
    __auto_type class = object_getClass(self);
    __auto_type method = class_getInstanceMethod(class, getter);
    if (!method)
        return;
    __auto_type oldValue = objc_msgSend(self, getter);
    __auto_type super = object_getSuper(self);
    
    foreach((NXHashTable *)objc_getAssociatedObject(self, &OBS_PRE_KEY), ^(id body) {
        !body ?: ((Callback)body)(newValue);
    });
    objc_msgSendSuper(&super, _cmd, newValue);
    
    foreach((NXHashTable *)objc_getAssociatedObject(self, &OBS_POST_KEY), ^(id body) {
        !body ?: ((Callback)body)(oldValue);
    });
}
