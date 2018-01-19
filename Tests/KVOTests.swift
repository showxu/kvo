//
//  KVOTests.swift
//  KVO Tests
//
//

import XCTest
@testable import KVO

class Object: NSObject {
    
    @objc dynamic var key = ""
}

class KVOTests: XCTestCase {
    
    override func setUp() {
        super.setUp()
        // Put setup code here. This method is called before the invocation of each test method in the class.
    }
    
    override func tearDown() {
        // Put teardown code here. This method is called after the invocation of each test method in the class.
        super.tearDown()
    }
    
    func testExample() {
        //let m = class_getInstanceMethod(KVOTests.self, #selector(setter: KVOTests.key));
        let o = Object()
        KVO.observe(o, for: "key", willSet: { (x: Any) in return
            print("callback")
        }, didSet: nil)
        // This is an example of a functional test case.
        // Use XCTAssert and related functions to verify your tests produce the correct results.
        o.key = "x"
        
    }
    
    func testPerformanceExample() {
        // This is an example of a performance test case.
        self.measure {
            // Put the code you want to measure the time of here.
        }
    }
}
