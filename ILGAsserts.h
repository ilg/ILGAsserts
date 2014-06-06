//
//  ILGAsserts.h
//
//  Created by Isaac Greenspan on 9/21/13.
//

/*********************************************************************************
 
 © Copyright 2013, Isaac Greenspan
 
 Permission is hereby granted, free of charge, to any person
 obtaining a copy of this software and associated documentation
 files (the "Software"), to deal in the Software without
 restriction, including without limitation the rights to use,
 copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the
 Software is furnished to do so, subject to the following
 conditions:
 
 The above copyright notice and this permission notice shall be
 included in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 OTHER DEALINGS IN THE SOFTWARE.
 
 *********************************************************************************/

#import <Foundation/Foundation.h>
#import <XCTest/XCTest.h>

/**
 *  Assert that a given block will return YES before a given time interval has elapsed.
 *
 *  @param isFinishedBlock A block taking no parameters and returning BOOL.  The waiting stops when this block returns YES.
 *  @param timeout         The maximum amount of time to wait, in seconds.
 *  @param format          The description for the assertion (optional).
 */
#define ILGAssertBlockReturnsYesBeforeTimeout(isFinishedBlock, timeout, format...) \
    do { \
        @try {\
            if (!ILGWaitForBlockUntilTimeout(isFinishedBlock, timeout)) { \
                _XCTRegisterFailure(_XCTFailureDescription(_XCTAssertion_Fail, 0), format); \
            } \
        }\
        @catch (id anException) {\
            _XCTRegisterFailure(_XCTFailureDescription(_XCTAssertion_Fail, 1), format); \
        }\
    } while(0)

/**
 *  Helper function to wait until either the timeout is reached or the isFinishedBlock returns YES, returning the last result of the block.
 *
 *  @param isFinishedBlock A block taking no parameters and returning BOOL.  The waiting stops when this block returns YES.
 *  @param timeout         The maximum amount of time to wait, in seconds.
 *
 *  @return The last value returned by isFinishedBlock, so NO if the timeout was reached, otherwise YES.
 */
extern BOOL ILGWaitForBlockUntilTimeout(BOOL(^isFinishedBlock)(void), NSTimeInterval timeout);

/**
 *  Helper function to "idle" by running the run loop for a specified amount of time.
 *
 *  @param idleInterval  The amount of time for which to idle, in seconds.
 */
extern void ILGIdleFor(NSTimeInterval idleInterval);