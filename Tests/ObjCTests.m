//
//  kvoTests.m
//  kvoTests
//
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
    observe(_observable, "key", _observable.will, _observable.did);
}

- (void)testMain {
    __auto_type values = @[@"v1", @"v2", @"v3", @"v4"];
    [values enumerateObjectsUsingBlock:^(id _Nonnull value, NSUInteger idx, BOOL * _Nonnull stop) {
        _observable.key = value;
        XCTAssert([_observable.key isEqualToString: value]);
    }];
}

@end
