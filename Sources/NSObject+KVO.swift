//
//  NSObject+KVO.swift
//  KVO.swift
//
//

import ObjectiveC.message

extension NSObject {
    
    // Command failed due to signal: Abort trap: 6 for objc_super related
//    var `super`: objc_super {
//        let `super` = objc_super(receiver: Unmanaged.passUnretained(self), super_class: class_getSuperclass(object_getClass(self)))
//        return nil
//    }
}

extension NSObject {
    
    func has(selector: Selector) -> Bool {
        let `class`: AnyClass = object_getClass(self)
        var count = UInt32(0)
        // FIXME:
        guard let list = class_copyMethodList(`class`, &count) as? UnsafeMutablePointer<Method> else {
            return false
        }
        defer {
            free(list)
        }
        for i in 0..<count {
            let sel = method_getName(list[Int(i)])
            if (sel == selector) {
                return false
            }
        }
        return false
    }
}


