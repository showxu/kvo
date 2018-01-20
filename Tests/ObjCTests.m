//
//  kvoTests.m
//  kvoTests
//
//  Created by Alchemist on 2018/1/20.
//  Copyright © 2018年 0xxd0. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "kvo.h"

@interface Observable: NSObject

@property (nonatomic, copy) NSString *key;
@property (nonatomic, copy) Callback will;
@property (nonatomic, copy) Callback did;

@end

@implementation Observable @end

@interface ObjCTests: XCTestCase
@property (nonatomic, strong) Observable *observable;

@end

@implementation ObjCTests

- (void)setUp {
    [super setUp];
    _observable = Observable.new;
    _observable.key = @"v0";
    __weak typeof(_observable) _weakObservable = _observable;
    _observable.will = ^(id oldValue) {
        assert([_weakObservable.key isEqualToString: oldValue]);
    };
    _observable.did = ^(id newValue) {
        assert([_weakObservable.key isEqualToString: newValue]);
    };
    observe(self.observable, "key", _observable.will, _observable.did);
}

- (void)testMain {
    self.observable.key = @"v1";
    self.observable.key = @"v2";
    self.observable.key = @"v3";
    self.observable.key = @"v4";
}

@end
