//
//  Selector+KVO.swift
//  KVO.swift
//
//

import Foundation.NSObjCRuntime

extension Selector {
    
    @_inlineable
    @_versioned
    func setter() -> Selector? {
        var sel = NSStringFromSelector(self)
        if (sel.count <= 0) {
            return nil;
        }
        sel = sel.uppercased(at: sel.startIndex)
        let setter = "set\(sel):"
        return Selector(setter)
    }
    
    @_inlineable
    @_versioned
    func getter() -> Selector? {
        var sel = NSStringFromSelector(self)
        guard sel.count > 0, sel.hasPrefix("set"), sel.hasSuffix(":") else {
            return nil;
        }
        sel = String(sel[sel.index(sel.startIndex, offsetBy: 3)..<sel.index(sel.endIndex, offsetBy: -1)])
        sel = sel.lowercased(at: sel.startIndex)
        return Selector(sel)
    }
}
