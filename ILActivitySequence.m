/**
 *  @file ILActivitySequence.m
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

#import "ILActivitySequence.h"


@interface ILActivitySequence()

-(void)runNextActivity:(id)previousResult start:(ILActivityStartedBlock)startBlock progress:(ILActivityProgressBlock)progressBlock end:(ILActivityEndedBlock)endedBlock error:(ILActivityErrorBlock)errorBlock;

@end

@implementation ILActivitySequence

-(id)init
{
    if ((self=[super init]))
    {
        _running=NO;
        activities=[[NSMutableArray array] retain];
    }
    
    return self;
}

-(void)dealloc
{
    [activities release];
    
    [super dealloc];
}

+(ILActivitySequence *)activitySequence
{
    return [[[ILActivitySequence alloc] init] autorelease];
}

-(void)addActivityLabeled:(NSString *)label block:(ILActivityBlock)activityBlock
{
    [activities addObject:[ILActivity activityForStep:activities.count+1 label:label block:activityBlock]];
}

-(BOOL)run
{
    return [self run:nil progress:nil end:nil error:nil];
}

-(BOOL)runSynchronously
{
    return [self runSynchronously:nil progress:nil end:nil error:nil];
}

-(BOOL)run:(ILActivityStartedBlock)startBlock progress:(ILActivityProgressBlock)progressBlock end:(ILActivityEndedBlock)endedBlock error:(ILActivityErrorBlock)errorBlock
{
    if (_running)
        return NO;
    
    if (activities.count==0)
        return NO;
    
    in_background(^{
        [self runSynchronously:startBlock progress:progressBlock end:endedBlock error:errorBlock];
    });
    
    return YES;
}

-(BOOL)runSynchronously:(ILActivityStartedBlock)startBlock progress:(ILActivityProgressBlock)progressBlock end:(ILActivityEndedBlock)endedBlock error:(ILActivityErrorBlock)errorBlock
{
    if (_running)
        return NO;
    
    if (activities.count==0)
        return NO;
    
    _running=YES;
    
    totalCount=activities.count;
    currentIndex=0;
    
    [self runNextActivity:nil start:startBlock progress:progressBlock end:endedBlock error:errorBlock];
    
    return YES;
}

-(void)abort
{
    _running=NO;
}

-(void)runNextActivity:(id)previousResult start:(ILActivityStartedBlock)startBlock progress:(ILActivityProgressBlock)progressBlock end:(ILActivityEndedBlock)endedBlock error:(ILActivityErrorBlock)errorBlock
{
    if (currentIndex==activities.count)
    {
        [self abort];
        return;
    }
    
    [self retain];
    
    ILActivity *activity=[activities objectAtIndex:currentIndex];
    
    currentIndex++;
    
    if (startBlock)
        startBlock(activity, totalCount);
    
    __block typeof(self) this=self;
    
    [activity run:previousResult
         progress:progressBlock
         complete:^(BOOL succeeded, id result, NSError *error) {
             
             if (endedBlock)
                 endedBlock(activity, totalCount);
             
             if (!succeeded)
             {
                 if (errorBlock)
                     errorBlock(activity, error);
                 
                 [this abort];
             }
             else
                 [this runNextActivity:result start:startBlock progress:progressBlock end:endedBlock error:errorBlock];
             
             [this release];
         }];
}

@end
