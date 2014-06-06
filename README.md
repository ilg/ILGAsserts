# ILGAsserts

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

