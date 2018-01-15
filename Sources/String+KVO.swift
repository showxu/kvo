//
//  String+KVO.swift
//  KVO.swift
//

extension String {
    
    @_inlineable
    @_versioned
    func uppercased(at idx: String.Index) -> String {
        guard self.count > 0 else {
            return self
        }
        let element = String(self[idx]).uppercased()
        guard idx > startIndex else {
        
            return "\(element)\(self[idx...])"
        }
        guard idx < endIndex else {
            let element = self[idx]
            return "\(self[...idx])\(element)"
        }
        let leading = self[...index(before: idx)]
        let trailing = self[index(after: idx)...]
        return "\(leading)\(element)\(trailing)"
    }
    
    @_inlineable
    @_versioned
    func lowercased(at idx: String.Index) -> String {
        guard self.count > 0 else {
            return self
        }
        let element = String(self[idx]).lowercased()
        guard idx > startIndex else {
            
            return "\(element)\(self[idx...])"
        }
        guard idx < endIndex else {
            let element = self[idx]
            return "\(self[...idx])\(element)"
        }
        let leading = self[...index(before: idx)]
        let trailing = self[index(after: idx)...]
        return "\(leading)\(element)\(trailing)"
    }
    
    @_inlineable
    @_versioned
    func hasPrefix(_ str: String)-> Bool {
        return (self as NSString).hasPrefix(str)
    }
    
    @_inlineable
    @_versioned
    func hasSuffix(_ str: String)-> Bool {
        return (self as NSString).hasSuffix(str)
    }
}
