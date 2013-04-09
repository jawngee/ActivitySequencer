/**
 *  @file ILActivitySequence.h
 *  @author Jon Gilkison
 *  @copyright Copyright (c) 2013 Interfacelab LLC. All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  - Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 *  This is a modified BSD license (the third clause has been removed).
 *  The BSD license may be found here:
 *
 *  http://www.opensource.org/licenses/bsd-license.php
 */

#import "ILActivity.h"

/**
 * Contains a sequence of activities
 */
@interface ILActivitySequence : NSObject
{
    NSMutableArray *activities;
@private
    NSInteger currentIndex;
    NSInteger totalCount;
}

@property (readonly) BOOL running;  /**< Flag to determine if the sequence is currently running */

/**
 * Creates a new sequence
 * @return The new sequence
 */
+(ILActivitySequence *)activitySequence;

/**
 * Adds a new activity to the list
 * @param label The label for the activity
 * @param activityBlock The block to run for the activity
 */
-(void)addActivityLabeled:(NSString *)label block:(ILActivityBlock)activityBlock;

/**
 * Aborts the running of the sequence.  Note this does not stop any currently running activity
 */
-(void)abort;

/**
 * Runs the sequence on the background thread asynchronously
 * @return NO if the sequence could not be run, otherwise YES
 */
-(BOOL)run;

/**
 * Runs the sequence on the current thread synchronously
 * @return NO if the sequence could not be run, otherwise YES
 */
-(BOOL)runSynchronously;

/**
 * Runs the sequence on the background thread asynchronously
 * @param startBlock The block called at the start of every activity step
 * @param progressBlock The block the activity calls to report progress
 * @param endedBlock The block that is called after the activity step runs
 * @param errorBlock The block that is called if any activity returns an error
 * @return NO if the sequence could not be run, otherwise YES
 */
-(BOOL)run:(ILActivityStartedBlock)startBlock progress:(ILActivityProgressBlock)progressBlock end:(ILActivityEndedBlock)endedBlock error:(ILActivityErrorBlock)errorBlock;

/**
 * Runs the sequence on the current thread synchronously
 * @param startBlock The block called at the start of every activity step
 * @param progressBlock The block the activity calls to report progress
 * @param endedBlock The block that is called after the activity step runs
 * @param errorBlock The block that is called if any activity returns an error
 * @return NO if the sequence could not be run, otherwise YES
 */
-(BOOL)runSynchronously:(ILActivityStartedBlock)startBlock progress:(ILActivityProgressBlock)progressBlock end:(ILActivityEndedBlock)endedBlock error:(ILActivityErrorBlock)errorBlock;

@end
