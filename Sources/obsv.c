//
//  observable.c
//  kvo
//
//

#include "obsv.h"
#include "obsv_private.h"
#include "stub.h"
#include "selproc.h"
#include "strproc.h"
#include "objc.h"
#include <objc/runtime.h>
#include <pthread/pthread.h>

void observe(id observable, char *key, Callback will, Callback did) {
    __auto_type class  = object_getClass((id)observable);
    __auto_type key_sel = sel_getUid(key);
    if (!key_sel) return;
    __auto_type setter_sel = sel_setter(key_sel);
    __auto_type setter = class_getInstanceMethod(class, setter_sel);
    if (!key_sel || !setter) {
        return;
    }
    __auto_type orig_class_name = class_getName(class);
    
    if (!strprefix(orig_class_name, OBSERVABLE_PREFIX)) {
        __auto_type len = strlen(OBSERVABLE_PREFIX) + strlen(orig_class_name);
        char dst[len];
        __auto_type observable_class_name = strcat(strcpy(dst, OBSERVABLE_PREFIX), orig_class_name);
        class = objc_createObservableClass(class, observable_class_name, 0);
        object_setClass(observable, class);
    }
    
    if (!class_contains(class, setter_sel)) {
        __auto_type types = method_getTypeEncoding(setter);
        class_addMethod(class, setter_sel, (IMP)_setter_impl_stub, types);
    }
    
    __auto_type table1 = (NXHashTable *)objc_getAssociatedObject(observable, &OBS_PRE_KEY) ?: NXCreateHashTable(NXPtrPrototype, 0, nil);
    NXHashInsert(table1, will);
    objc_setAssociatedObject(observable, &OBS_PRE_KEY, (id)table1, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
    
    __auto_type table2 = (NXHashTable *)objc_getAssociatedObject(observable, &OBS_POST_KEY) ?: NXCreateHashTable(NXPtrPrototype, 0, nil);
    NXHashInsert(table2, did);
    
    objc_setAssociatedObject(observable, &OBS_POST_KEY, (id)table2, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

NXHashTable *observable_getpreobservers(id observable) {
    if (!observable) return nil;
    __auto_type table = (NXHashTable *)objc_getAssociatedObject(observable, &OBS_PRE_KEY) ?: NXCreateHashTable(NXPtrPrototype, 0, nil);
    return table;
}

NXHashTable *observable_getpostobservers(id observable) {
    if (!observable) return nil;
    __auto_type table = (NXHashTable *)objc_getAssociatedObject(observable, &OBS_POST_KEY) ?: NXCreateHashTable(NXPtrPrototype, 0, nil);
    return table;
}

