//
//  KVO.stub.swift
//  KVO.swift
//
//

import ObjectiveC.runtime

// Since the fucntion pointer is not available in Swift, we use @convention(c) to stub the setter
// instead of Swift func
// (https://stackoverflow.com/questions/43880839/swift-unable-to-cast-function-pointer-to-void-for-use-in-c-style-third-party)
struct _Stub {
    
    typealias _Setter  = @convention(c) (_ self: NSObject , _ _cmd: Selector, _ newValue: Any) -> Void
}

let __setter__: _Stub._Setter = { (self, _cmd, newValue) -> Void in
    let sel = _cmd.getter()
    let key = NSStringFromSelector(sel!)
    let cls: AnyClass = object_getClass(self)
    
    guard let _ = class_getInstanceMethod(cls, sel) else {
        // FIXME: throw error
        return
    }
    let oldValue = self.value(forKey: key)!
    
    //let _ = objc_super(receiver: anyObject, super_class: superClass)
    var `super` = object_getSuper(self)
   
    var ctx: Observable.Context =
        objc_getAssociatedObject(self, Observable.ContextKey) as? Observable.Context ?? [
            Observable.willSet: [],
            Observable.didSet: []
        ]

    if let willSet = ctx[Observable.willSet] {
        willSet.forEach({ (body) in
            DispatchQueue.main.async {
                body(newValue)
            }
        })
    }

    object_msgSendSuper(&`super`, _cmd, newValue)
    
    if let didSet = ctx[Observable.didSet] {
        didSet.forEach({ (body) in
            DispatchQueue.main.async {
                body(oldValue)
            }
        })
    }
}

