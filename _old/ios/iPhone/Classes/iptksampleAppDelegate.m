

#import "iptksampleAppDelegate.h"
#import "EAGLView.h"
//#import "KPTK.h"

@implementation iptksampleAppDelegate

@synthesize window;
@synthesize glView;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    [glView startAnimation];
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    [glView stopAnimation];
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    [glView startAnimation];
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    [glView stopAnimation];
	[glView quitApplication];
}

- (void)dealloc
{
    [window release];
    [glView release];

    [super dealloc];
}

- (void) didReceiveMemoryWarning {

// Releases the view if it doesn't have a superview.

    [super didReceiveMemoryWarning];

// Release any cached data, images, etc that aren't in use.

}

@end
