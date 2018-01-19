//
//  KVO.stub.swift
//  KVO.swift
//
//

import Foundation
import ObjectiveC.runtime

// Since the fucntion pointer is not available in Swift, we use @convention(c) to stub the setter
// instead of Swift func
// (https://stackoverflow.com/questions/43880839/swift-unable-to-cast-function-pointer-to-void-for-use-in-c-style-third-party)

typealias _setter_stub_impl_type = @convention(c) (_ self: NSObject , _ _cmd: Selector, _ newValue: Any) -> Void

@_silgen_name("objc_msgSendSuper") func objc_msgSendSuper(_: UnsafeMutablePointer<objc_super>, _: Selector, _: Any) -> Void

@_silgen_name("objc_msgSend") func objc_msgSend(_: AnyObject, _: Selector, _: Any) -> Void

@_silgen_name("object_getSuper") func object_getSuper(_: AnyObject) -> objc_super

let _setter_stub_impl: _setter_stub_impl_type = { (`self`, _cmd, newValue) -> Void in
    let sel = _cmd.getter()
    let key = NSStringFromSelector(sel!)
    let cls: AnyClass = object_getClass(self)!
    
    guard let _ = class_getInstanceMethod(cls, sel) else {
        // FIXME: throw error
        return
    }
    let oldValue = self.value(forKey: key)!
    
    // FIXME: fire a bug
    // Command failed due to signal: Abort trap: 6
    // IntToPtr source must be an integral
    //    %4 = inttoptr %swift.type* %1 to %objc_class*, !dbg !178
    // var _spr = objc_super(receiver: Unmanaged.passUnretained(`self`),
    //                       åsuper_class: class_getSuperclass(object_getClass(`self`)))
    // use c function bridge
    var spr = object_getSuper(`self`)
    
    var ctx: Observable.Context =
        objc_getAssociatedObject(self, Observable.contextKey) as? Observable.Context ?? [
            Observable.willSet: [],
            Observable.didSet: []
        ]

    if let willSet = ctx[Observable.willSet] {
        willSet.forEach({ (body) in
            (body as? ((Any) -> Void))?(newValue)
        })
    }
  
    // @objc thunk lookUpImpOrForward crash
    // objc_msgSendSuper(&spr, _cmd, newValue)
    
    if let didSet = ctx[Observable.didSet] {
        didSet.forEach({ (body) in
            (body as? ((Any) -> Void))?(oldValue)
        })
    }
}

let _class_impl_stub: @convention (c) (_ self: AnyClass, _ _cmd: Selector) -> Void = { (`self`, _cmd) -> Void in
    return class_getSuperclass(object_getClass(self));
}

