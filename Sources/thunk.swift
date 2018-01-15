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
        String: [Observable.Callback]
    ]
    
    static let ContextKey = Array(["Context".utf8CString])
    
    static let prefix =  "Observable."
    static let willSet = prefix + "willSet"
    static let didSet = prefix + "didSet"
}

public func observe<ObservableType, KeyType>(
    _ observable: ObservableType,
    for keyPath: String,
    willSet: ((_ newValue: KeyType) -> Void)? = nil,
    didSet: ((_ oldValue: KeyType) -> Void)? = nil) where ObservableType: NSObject {
    
    var cls: AnyClass?  = object_getClass(observable)
    let setterSel = NSSelectorFromString(keyPath).setter()
    guard let setterMethod = class_getInstanceMethod(cls, setterSel) else {
        // FIXME: throw Error
        return
    }
    let origName = String(cString: class_getName(cls))
    
    if !origName.hasPrefix(Observable.prefix) {
        let observableName = Array(Observable.prefix.utf8CString + origName.utf8CString)
        cls = objc_createObservableClass(cls!, observableName,  0)
        object_setClass(observable, cls)
    }
    let stub = unsafeBitCast(__setter__, to: OpaquePointer.self)
    
    if !observable.has(selector: setterSel!) {
        let types = method_getTypeEncoding(setterMethod)
        class_addMethod(cls, setterSel!, stub, types);
    }
    
    var ctx: Observable.Context =
        objc_getAssociatedObject(observable, Observable.ContextKey) as? Observable.Context ?? [
            Observable.willSet: [],
            Observable.didSet: []
        ]
    if willSet != nil {
        ctx[Observable.willSet]?.append(willSet as! Observable.Callback)
    }
    if didSet != nil {
        ctx[Observable.didSet]?.append(didSet as! Observable.Callback)
    }
    objc_setAssociatedObject(observable, Observable.ContextKey, ctx, .OBJC_ASSOCIATION_RETAIN_NONATOMIC)
}

