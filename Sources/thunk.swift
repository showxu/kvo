//
//  KVO.swift
//  KVO.swift
//
//

import Foundation.NSObjCRuntime
import ObjectiveC.objc
import os.base

public struct Observable {
    
    public typealias Callback = (_ newValue: Any) -> Void
    
    typealias Context = [
        String: [Any]
    ]
    
    static let contextKey = Array(["Context".utf8CString])
    
    static let prefix = "Observable."
    static let willSet = prefix + "willSet"
    static let didSet = prefix + "didSet"
}

public func observe<ObservableType>(
    _ observable: ObservableType,
    for keyPath: String,
    willSet: ((_ newValue: Any) -> Void)? = nil,
    didSet: ((_ oldValue: Any) -> Void)? = nil) where ObservableType: NSObject {
    
    var cls: AnyClass?  = object_getClass(observable)
    let setterSel = NSSelectorFromString(keyPath).setter()
    guard let setterMethod = class_getInstanceMethod(cls, setterSel!) else {
        // FIXME: throw Error
        return
    }
    let origName = String(cString: class_getName(cls))
    
    if !origName.hasPrefix(Observable.prefix) {
        let observableName = Observable.prefix + origName
        cls = objc_createObservableClass(cls!, observableName, 0)
        object_setClass(observable, cls!)
    }
    let stub = unsafeBitCast(_setter_stub_impl, to: OpaquePointer.self)
    
    if !class_containsInstanceMethod(cls!, setterSel!) {
        let types = method_getTypeEncoding(setterMethod)
        class_addMethod(cls, setterSel!, stub, types);
    }
    
    var ctx: Observable.Context =
        objc_getAssociatedObject(observable, Observable.contextKey) as? Observable.Context ?? [
            Observable.willSet: [],
            Observable.didSet: []
        ]
    if willSet != nil {
        ctx[Observable.willSet]?.append(willSet as Any)
    }
    if didSet != nil {
        ctx[Observable.didSet]?.append(didSet as Any)
    }
    objc_setAssociatedObject(observable, Observable.contextKey, ctx, .OBJC_ASSOCIATION_RETAIN_NONATOMIC)
}

