//
//  ILGAsserts.h
//
//  Created by Isaac Greenspan on 9/21/13.
//

/*********************************************************************************
 
 © Copyright 2013-2014, Isaac Greenspan
 
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

// Apple changed the signature for the _XCTRegisterFailure macro between iOS 7 and iOS 8.
#if defined(__IPHONE_8_0) && __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_8_0
#   define _ILGRegisterFailure(expression, format...) _XCTRegisterFailure(self, expression, format)
#else
#   define _ILGRegisterFailure(expression, format...) _XCTRegisterFailure(expression, format)
#endif


/**
 *  Assert that a given array is not empty and that every element it contains is of the kind of the given class.
 *
 *  @param array     The array to test
 *  @param class     The class that every array element should be a kind of
 *  @param format    The description for the assertion (optional).
 */
#define ILGAssertNonemptyArrayOfClass(array, class, format...) \
    do { \
        @try {\
            if ([array count] == 0) { \
                _ILGRegisterFailure(_XCTFailureDescription(_XCTAssertion_Fail, 0), format); \
            } else { \
                for (id ILGAssertNonemptyArrayOfClass_obj in array) { \
                    if (![ILGAssertNonemptyArrayOfClass_obj isKindOfClass:class]) { \
                        _ILGRegisterFailure(_XCTFailureDescription(_XCTAssertion_Fail, 0), format); \
                        break; \
                    } \
                } \
            } \
        }\
        @catch (id anException) {\
            _ILGRegisterFailure(_XCTFailureDescription(_XCTAssertion_Fail, 1), format); \
        }\
    } while(0)

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
                _ILGRegisterFailure(_XCTFailureDescription(_XCTAssertion_Fail, 0), format); \
            } \
        }\
        @catch (id anException) {\
            _ILGRegisterFailure(_XCTFailureDescription(_XCTAssertion_Fail, 1), format); \
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