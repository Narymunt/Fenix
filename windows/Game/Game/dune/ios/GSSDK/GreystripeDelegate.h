/*
 *  GreystripeDelegate.h
 *
 *  Copyright 2009 Greystripe, Inc. All rights reserved.
 *
 */

@protocol GreystripeDelegate<NSObject>

@optional
/**
 * Sent by the Greystripe SDK whenever a Greystripe display is about to open,
 * such as an advertisement, or an advertisement loading screen.  Upon receiving
 * this message, the application should pause gameplay or music or other
 * processor-intensive activities in order to ensure that ads perform properly.
 */
- (void)greystripeDisplayWillOpen;
/**
 * Sent by the Greystripe SDK whenever the last open Greystripe display is
 * about to close.  Upon receiving this message, the application should resume
 * any gameplay or music or other processor-intensive activities that were
 * halted in response to greystripeDisplayWillOpen.
 */
- (void)greystripeDisplayWillClose;
/**
 * Sent by the Greystripe SDK when it receives didReceiveMemoryWarning from the
 * device.  This is sent as a courtesy to applications that may not use
 * UIViewControllers to control their primary view, and as such will not receive
 * the notification on their own.  In the event that an application receives
 * this message, the app should free up as much of its own memory as possible,
 * such as dumping caches that aren't absolutely necessary.
 *
 * Note that it is important to not respond to this message by calling 
 * GSDealloc, as doing so will result in undefined behavior of the Greystripe
 * SDK.
 */
- (void)greystripeDidReceiveMemoryWarning;

@end
