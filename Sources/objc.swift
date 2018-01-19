//
//  objc.swift
//  KVO
//
//

public func objc_createObservableClass(_ super: AnyClass,
                                       _ name: String,
                                       _ extraBytes: size_t) -> AnyClass? {
    // objc_duplicateClass(Class  _Nonnull __unsafe_unretained original, const char * _Nonnull name, size_t extraBytes)
    if let aCls = objc_getClass(name) {
        return aCls as? AnyClass
    }
    let stub = unsafeBitCast(_class_impl_stub, to: OpaquePointer.self)
    let sel = sel_getUid("class")
    
    if let newCls = objc_allocateClassPair(`super`, name.utf8CString.baseAddress!, 0),
        let clsMethod = class_getClassMethod(newCls, sel) {
        class_addMethod(object_getClass(newCls), sel, stub, method_getTypeEncoding(clsMethod));
        objc_registerClassPair(newCls);
        return newCls;
    }
    return nil;
}

public func class_containsInstanceMethod(_ cls: AnyClass, _ name: Selector) -> Bool {
    var count = UInt32(0)
    // FIXME:
    let list = class_copyMethodList(cls, &count)
    defer {
        free(list)
    }
    for i in 0..<count {
        let sel = method_getName(list![Int(i)])
        if sel == name {
            return true
        }
    }
    return false
}
