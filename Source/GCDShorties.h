//
//  GCDShorties.h
//
//  Created by Jon Gilkison on 1/8/13.
//  Copyright (c) 2013 Interfacelab LLC. All rights reserved.
//

#ifndef iLab_GCDShorties_h
#define iLab_GCDShorties_h

typedef void(^VoidBlock)();

/**
 * Runs the block in the background
 * @param block The block to run
 */
extern void in_background(VoidBlock block);

/**
 * Runs the block on the main thread asynchronously
 * @param block The block to run
 */
extern void on_main(VoidBlock block);

/**
 * Runs the block on the main thread synchronously
 * @param block The block to run
 */
extern void on_main_sync(VoidBlock block);


#endif
