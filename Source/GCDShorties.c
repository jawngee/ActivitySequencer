//
//  GCDShorties.c
//  VMix
//
//  Created by Jon Gilkison on 1/8/13.
//  Copyright (c) 2013 Interfacelab LLC. All rights reserved.
//

#include "GCDShorties.h"

#include <stdio.h>
#include <dispatch/dispatch.h>

void in_background(VoidBlock block)
{
    dispatch_async(dispatch_get_global_queue(0, 0), block);
}

void on_main(VoidBlock block)
{
    if (dispatch_get_current_queue()==dispatch_get_main_queue())
        block();
    else
        dispatch_async(dispatch_get_main_queue(), block);
}

void on_main_sync(VoidBlock block)
{
    if (dispatch_get_current_queue()==dispatch_get_main_queue())
        block();
    else
        dispatch_sync(dispatch_get_main_queue(), block);
}

