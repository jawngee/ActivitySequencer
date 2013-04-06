/**
 *  @file ILActivity.h
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


#import <Foundation/Foundation.h>

@class ILActivity;

/** Called when an activity is about to start */
typedef void (^ILActivityStartedBlock)(ILActivity *activity, NSInteger totalSteps);

/** Called by the activity to indicate progress */
typedef void (^ILActivityProgressBlock)(ILActivity *activity, float progress);

/** Called when an activity has finished */
typedef void (^ILActivityEndedBlock)(ILActivity *activity, NSInteger totalSteps);

/** Called when an activity generates an error */
typedef void (^ILActivityErrorBlock)(ILActivity *activity, NSError *error);

/** Activity calls this with its result */
typedef void (^ILActivityCompleteBlock)(BOOL succeeded, id result, NSError *error);

/** The activity block */
typedef void (^ILActivityBlock)(ILActivity *activity, id previousResult, ILActivityProgressBlock progressBlock, ILActivityCompleteBlock completeBlock);


/**
 * Represents a single step in the activity list
 */
@interface ILActivity : NSObject

@property (assign, nonatomic) NSInteger step;                   /**< The step number */
@property (copy, nonatomic) NSString *label;                    /**< The label for the activity */
@property (copy, nonatomic) ILActivityBlock activityBlock;      /**< The actual activity block that gets called when run */

/**
 * Creates a new activity
 * @param step The step number for this activity
 * @param label The label/name for this activity
 * @param block The block to run when this activity is run 
 * @return The new activity
 */
+(ILActivity *)activityForStep:(NSInteger)step label:(NSString *)label block:(ILActivityBlock)activityBlock;

/**
 * Runs the activity
 * @param previousResult The result from the activity that was run prior to this
 * @param progressBlock The progress block to call from within the activity
 * @param completeBlock The block the activity calls when finished running
 */
-(void)run:(id)previousResult progress:(ILActivityProgressBlock)progressBlock complete:(ILActivityCompleteBlock)completeBlock;

@end
