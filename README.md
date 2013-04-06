ActivitySequencer
=================

A block sequencer for objective-c based heavily on berzniz's brilliant [Sequencer](https://github.com/berzniz/Sequencer).

It has been expanded upon to allow for the separation of the running of activities and any UI that would report its progress.

Simple Usage
============

	ILActivitySequence *sequence=[ILActivitySequence activitySequence];
    [sequence addActivityLabeled:@"Step 1"
                           block:^(ILActivity *activity, id previousResult, ILActivityProgressBlock progressBlock, ILActivityCompleteBlock completeBlock) {
                               NSLog(@"Running activity %@",activity.label);
                               
                               // report some progress
                               progressBlock(activity, 1.0f);
                               
                               // We are done so call the completeBlock, passing this activity's label to the next step
                               completeBlock(YES, activity.label, nil);
                           }];
    
    [sequence addActivityLabeled:@"Step 2"
                           block:^(ILActivity *activity, id previousResult, ILActivityProgressBlock progressBlock, ILActivityCompleteBlock completeBlock) {
                               NSLog(@"Previous activity %@",previousResult);
                               
                               NSLog(@"Running activity %@",activity.label);
                               
                               // report some progress
                               progressBlock(activity, 1.0f);
                               
                               // We are done so call the completeBlock, passing this activity's label to the next step
                               completeBlock(YES, activity.label, nil);
                           }];
    
    [sequence run];
    
The output looks like:

	Running activity Step 1
	Previous activity Step 1
	Running activity Step 2

In this very basic example, we set up a sequence that runs two steps on a background thread.  If we wanted to run it on the current thread and wait for it to finish running, we'd change the last line to:

	[sequence runSynchronously];
	
Once a sequence has run, it will release itself, so you normally wouldn't have to worry about doing that.

However, unlike berzniz's Sequencer, ActivitySequencer doesn't release the steps as the are run.  This allows you to create sequences that you can run and run again.  In this case, you will need to retain and release the sequence yourself.

Advanced Usage
==============
To help insure separation of concerns and to keep your UI out of your model code, ActivitySequencer allows you to pass in blocks that you can use to report progress through your UI, or just to keep tabs on what is going on.

	ILActivitySequence *sequence=[ILActivitySequence activitySequence];
    [sequence addActivityLabeled:@"Step 1"
                           block:^(ILActivity *activity, id previousResult, ILActivityProgressBlock progressBlock, ILActivityCompleteBlock completeBlock) {
                               NSLog(@"Running activity %@",activity.label);
                               
                               // report some progress
                               progressBlock(activity, 1.0f);
                               
                               // We are done so call the completeBlock, passing this activity's label to the next step
                               completeBlock(YES, activity.label, nil);
                           }];
    
    [sequence addActivityLabeled:@"Step 2"
                           block:^(ILActivity *activity, id previousResult, ILActivityProgressBlock progressBlock, ILActivityCompleteBlock completeBlock) {
                               NSLog(@"Previous activity %@",previousResult);
                               
                               NSLog(@"Running activity %@",activity.label);
                               
                               // report some progress
                               progressBlock(activity, 1.0f);
                               
                               // We are done so call the completeBlock, passing this activity's label to the next step
                               completeBlock(YES, activity.label, nil);
                           }];
                      
	[sequence run:^(ILActivity *activity, NSInteger totalSteps) {
	        NSLog(@"Step %d - '%@' started.",activity.step,activity.label);
	    }
	         progress:^(ILActivity *activity, float progress) {
	             NSLog(@"Step %d - '%@' progress: %f.",activity.step,activity.label,progress);
	         }
	              end:^(ILActivity *activity, NSInteger totalSteps) {
	                  NSLog(@"Step %d - '%@' ended.",activity.step,activity.label);
	              }
	            error:^(ILActivity *activity, NSError *error) {
	                NSLog(@"Step %d - '%@' error: %@",activity.step,activity.label,[error localizedDescription]);
	            }];
	            
You'll see that the run message has 4 block parameters.  The first block is called right *before* the step is run.  The second block is the progress block that each activity will call.  The third block is called *after* the step is run.  The fourth block is called if the step doesn't run successfully.

The output looks like:

	
	Step 1 - 'Step 1' started.
	Running activity Step 1
	Step 1 - 'Step 1' progress: 1.000000.
	Step 1 - 'Step 1' ended.
	Step 2 - 'Step 2' started.
	Previous activity Step 1
	Running activity Step 2
	Step 2 - 'Step 2' progress: 1.000000.
	Step 2 - 'Step 2' ended.


