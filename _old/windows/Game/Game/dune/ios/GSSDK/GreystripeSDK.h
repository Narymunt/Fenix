/**
 *  GreystripeSDK.h
 *
 *  Copyright 2009 Greystripe, Inc. All rights reserved.
 *
 */

#ifndef _GREYSTRIPE_H
#define _GREYSTRIPE_H

/**
 * To install the Greystripe SDK into your XCode project, from the Project menu
 * choose "Add to Project", and add libGreystripeSDK.a, GreystripeDelegate.h,
 * and GreystripeSDK.h to your project.  The SDK requires no additional
 * resource files, but it does require a number of Apple's frameworks to be
 * included as well.  Right-click on your project in the Groups & Files view, 
 * and click "Add", and click "Existing Frameworks...". From the 
 * "/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/
 * [YOUR_BASE_SDK]/System/Library/Frameworks" folder, add 
 * CoreGraphics.framework, MediaPlayer.framework, OpenAL.framework, 
 * OpenGLES.framework, QuartzCore.framework, and SystemConfiguration.framework
 * if they're not already included in your project.  Then, from the 
 * "/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/[YOUR_BASE_SDK]/usr/lib" 
 * folder, add libz.dylib and libsqlite3.dylib if they're not already included
 * in your project.
 */

typedef long long GSValue;

#ifdef __cplusplus
extern "C"
{
#endif

	/**
	 * Invoke this once during application startup to initialize the Greystripe
	 * ad client.  This function must be called before any other Greystripe 
	 * functions are called.
	 *
	 * @param a_appID			the ID of your application as displayed in your
	 *							account on greystripe.com
	 */
	void GSInit(const char * a_appID);
	
	/**
	 * Sets the delegate class to handle Greystripe events, such as 
	 * greystripeDisplayWillOpen, which many applications will want to handle
	 * in order to pause activity when an advertisement is opened.  For more 
	 * information see GreystripeDelegate.h.
	 *
	 * @param a_delegate	The delegate class instance, which must implement 
	 *						the GreystripeDelegate protocol.
	 */
	void GSSetDelegate(void * a_delegate);
	
	/**
	 * Displays the next ad.
	 *
	 * @return	YES, if an ad will be displayed.  If there is no ad currently 
	 *			ready or the device has no network connection the ad system 
	 *			will return NO.  The application can handle this by tracking
	 *			the number of failed attempts and nagging the user to connect
	 *			to the network after trying too	many times.
	 */
	BOOL GSDisplayAd();
	
	/**
	 * Sets the relative rotation for ad display.  The value should be relative
	 * to the orientation the iPhone had on startup.  For example, many 3D 
	 * games are rendered as landscape applications, but the iPhone is actually
	 * in portrait orientation, and the game is just rendered with a 90 degree
	 * transformation.  In that case, the relative rotation of the ads should
	 * be the same 90 degrees, so the ads are displayed aligned with the 
	 * gameplay.  Games that actually use landscape mode from the iPhone OS 
	 * level, or games that are in portrait mode should specify 0 degrees.
	 * 
	 * Calls to this function while the ad display is open will be ignored to 
	 * ensure the most coherent ad viewing experience.
	 *
	 * @param a_rotation	Angle of the rotation.
	 */
	void GSSetRelativeRotation(float a_rotation);
	
	/**
	 * Return the version string corresponding to this version and build of the
	 * Greystripe SDK.  This is provided for convenience during testing as a
	 * way to ensure that you are using the proper version and build of the 
	 * Greystripe SDK.
	 * 
	 * @return	the version string
	 */
	const char * GSSDKVersion();
	
	/**
	 * Invoke this at application shutdown to shut down the Greystripe ad 
	 * client. This will release all major resources associated with the 
	 * GreystripeSDK. The memory freed by calling this function may not be 
	 * equal to the memory allocated since instantiating the SDK due to 
	 * internal caching of data in some native classes such as the web view.
	 *
	 * Note that invoking this function at any point other than application 
	 * shutdown will lead to undefined behavior of the Greystripe SDK.
	 */
	void GSDealloc();
		
#ifdef __cplusplus
}
#endif

#endif
