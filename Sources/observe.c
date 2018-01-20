//
//  observable.c
//  kvo
//
//

#include "observe.h"
#include "observe_priv.h"
#include "stub.h"
#include "objc_selproc.h"
#include "strproc.h"
#include "objc_core.h"
#include <objc/runtime.h>
#include <pthread/pthread.h>
#include <CoreFoundation/CoreFoundation.h>

void observe(id observable, const char *key, Callback will, Callback did) {
    __auto_type class  = object_getClass((id)observable);
    __auto_type key_sel = sel_getUid(key);
    if (!key_sel) return;
    __auto_type setter_sel = sel_setter(key_sel);
    __auto_type setter = class_getInstanceMethod(class, setter_sel);
    if (!key_sel || !setter) {
        return;
    }
    __auto_type orig_class_name = class_getName(class);
    
    if (!strpre(orig_class_name, OBSERVE_PREFIX)) {
        __auto_type len = strlen(OBSERVE_PREFIX) + strlen(orig_class_name);
        char dst[len];
        __auto_type observable_class_name = strcat(strcpy(dst, OBSERVE_PREFIX), orig_class_name);
        class = objc_createObservableClass(class, observable_class_name, 0);
        object_setClass(observable, class);
    }
    
    if (!class_contains(class, setter_sel)) {
        __auto_type types = method_getTypeEncoding(setter);
        class_addMethod(class, setter_sel, (IMP)_setter_impl_stub, types);
    }

    __auto_type table1 = (NXHashTable *)objc_getAssociatedObject(observable, OBSERVE_PRE_KEY) ?: NXCreateHashTable(NXPtrPrototype, 0, nil);
    NXHashInsert(table1, will);
    objc_setAssociatedObject(observable, OBSERVE_PRE_KEY, (void *)table1, OBJC_ASSOCIATION_ASSIGN);

    __auto_type table2 = (NXHashTable *)objc_getAssociatedObject(observable, OBSERVE_POST_KEY) ?: NXCreateHashTable(NXPtrPrototype, 0, nil);
    NXHashInsert(table2, did);
    
    objc_setAssociatedObject(observable, OBSERVE_POST_KEY, (void *)table2, OBJC_ASSOCIATION_ASSIGN);
}

NXHashTable *observable_getpreobservers(id observable) {
    if (!observable) return nil;
    __auto_type table = (NXHashTable *)objc_getAssociatedObject(observable, &OBSERVE_PRE_KEY) ?: NXCreateHashTable(NXPtrPrototype, 0, nil);
    return table;
}

NXHashTable *observable_getpostobservers(id observable) {
    if (!observable) return nil;
    __auto_type table = (NXHashTable *)objc_getAssociatedObject(observable, &OBSERVE_POST_KEY) ?: NXCreateHashTable(NXPtrPrototype, 0, nil);
    return table;
}

