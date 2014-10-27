# ILGAsserts

**Note:** Version 1.1.1 includes a fix for the change in `XCTest` in Xcode 6 that broke the `ILGAsserts` assertion macros—the fix works on iOS, but has not yet been tested on OS X.

## ILGAssertNonemptyArrayOfClass

`ILGAssertNonemptyArrayOfClass` asserts that a given array is not empty and that every element it contains is of the kind of the given class.  Example:

    ILGAssertNonemptyArrayOfClass(@[ @1, @NO, ], [NSNumber class], @"The given array is empty or contains an object that isn't an NSNumber.");  // Pass
    ILGAssertNonemptyArrayOfClass(@[ @1, @"NO", ], [NSNumber class], @"The given array is empty or contains an object that isn't an NSNumber.");  // Fail
    ILGAssertNonemptyArrayOfClass(@[ ], [NSNumber class], @"The given array is empty or contains an object that isn't an NSNumber.");  // Fail


## ILGAssertBlockReturnsYesBeforeTimeout

`ILGAssertBlockReturnsYesBeforeTimeout` asserts that a given block will return `YES` before a given time interval has elapsed.  Example:

    AFHTTPClient *client = [[AFHTTPClient alloc] initWithBaseURL:[NSURL URLWithString:@"http://ip.jsontest.com/"]];
    [client registerHTTPOperationClass:[AFJSONRequestOperation class]];
    [client setDefaultHeader:@"Accept" value:@"application/json"];

    __block BOOL done = NO;
    [client getPath:@""
         parameters:nil
            success:^(AFHTTPRequestOperation *operation, id responseObject) {
                NSLog(@"Success: %@", responseObject);
                done = YES;
            }
            failure:^(AFHTTPRequestOperation *operation, NSError *error) {
                NSLog(@"Failure: %@", error);
                done = YES;
            }];

    ILGAssertBlockReturnsYesBeforeTimeout(^{ return done; },  // Wait until done is YES
                                          5.0,  // Wait up to 5 seconds.
                                          @"Call failed to return quickly enough.");

