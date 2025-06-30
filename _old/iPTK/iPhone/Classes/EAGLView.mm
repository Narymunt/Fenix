

#import "EAGLView.h"
#import "ES1Renderer.h"
#include "KInput.h"

@implementation EAGLView

@synthesize animating;
@dynamic animationFrameInterval;

#define kAccelerometerFrequency		50 // 100 // Hz
#define kFilteringFactor			0.1 // For filtering out gravitational affects
#define kRenderingFPS				100.0 // Hz
#define kListenerDistance			1.0  // Used for creating a realistic sound field


// You must implement this method
+ (Class)layerClass
{
    return [CAEAGLLayer class];
}

//The EAGL view is stored in the nib file. When it's unarchived it's sent -initWithCoder:
- (id)initWithCoder:(NSCoder*)coder
{    
    if ((self = [super initWithCoder:coder]))
    {
        // Get the layer
        CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;

        eaglLayer.opaque = TRUE;
        eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                        [NSNumber numberWithBool:FALSE], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];

		renderer = [[ES1Renderer alloc] init];

        animating = FALSE;
        displayLinkSupported = FALSE;
        animationFrameInterval = 1;
        displayLink = nil;
        animationTimer = nil;

        // A system version of 3.1 or greater is required to use CADisplayLink. The NSTimer
        // class is used as fallback when it isn't available.
        NSString *reqSysVer = @"3.1";
        NSString *currSysVer = [[UIDevice currentDevice] systemVersion];
        if ([currSysVer compare:reqSysVer options:NSNumericSearch] != NSOrderedAscending)
            displayLinkSupported = TRUE;
    }

    return self;
}

- (void)drawView:(id)sender
{
    [renderer render];
}

- (void)layoutSubviews
{
    [renderer resizeFromLayer:(CAEAGLLayer*)self.layer];
    [self drawView:nil];
}

- (NSInteger)animationFrameInterval
{
    return animationFrameInterval;
}

- (void)setAnimationFrameInterval:(NSInteger)frameInterval
{
    // Frame interval defines how many display frames must pass between each time the
    // display link fires. The display link will only fire 30 times a second when the
    // frame internal is two on a display that refreshes 60 times a second. The default
    // frame interval setting of one will fire 60 times a second when the display refreshes
    // at 60 times a second. A frame interval setting of less than one results in undefined
    // behavior.
    if (frameInterval >= 1)
    {
        animationFrameInterval = frameInterval;

        if (animating)
        {
            [self stopAnimation];
            [self startAnimation];
        }
    }
}

- (void)startAnimation
{
    if (!animating)
    {
        if (displayLinkSupported)
        {
            // CADisplayLink is API new to iPhone SDK 3.1. Compiling against earlier versions will result in a warning, but can be dismissed
            // if the system version runtime check for CADisplayLink exists in -initWithCoder:. The runtime check ensures this code will
            // not be called in system versions earlier than 3.1.

            displayLink = [NSClassFromString(@"CADisplayLink") displayLinkWithTarget:self selector:@selector(drawView:)];
            [displayLink setFrameInterval:animationFrameInterval];
            [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
        }
        else
            animationTimer = [NSTimer scheduledTimerWithTimeInterval:(NSTimeInterval)((1.0 / 60.0) * animationFrameInterval) target:self selector:@selector(drawView:) userInfo:nil repeats:TRUE];

        animating = TRUE;
    }
}

- (void)stopAnimation
{
    if (animating)
    {
        if (displayLinkSupported)
        {
            [displayLink invalidate];
            displayLink = nil;
        }
        else
        {
            [animationTimer invalidate];
            animationTimer = nil;
        }

        animating = FALSE;
    }
}

- (void)dealloc
{
    [renderer release];

    [super dealloc];
}


// Input ====================================

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event 
{
	NSSet *allTouches = [event allTouches];
	int i, len=[allTouches count];
	
	//	NSLog(@"touchesBegan %d", len);
	
	for(i=0 ; i<len ; i++) 
	{
		UITouch *touch = [[allTouches allObjects] objectAtIndex:i];
		CGPoint location = [touch locationInView:self];
		KInput::setFingerPosition(i, location.x, location.y, true);	
		//	NSLog(@"KInput::setFingerPosition %d (%d %d) true", i, (int)location.x, (int)location.y);
		if(i==0) {			
			KInput::setScreenPressed([touch tapCount], location.x, location.y);
		}
	}
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event 
{
	NSSet *allTouches = [event allTouches];
	
	UITouch *touch = [[allTouches allObjects] objectAtIndex:0];
	CGPoint location = [touch locationInView:self];
	KInput::setFingerPosition(0, location.x, location.y, true);
	KInput::setScreenMoving(location.x, location.y);
	
	if([allTouches count] > 1) {
		touch = [[allTouches allObjects] objectAtIndex:1];
		location = [touch locationInView:self];
		KInput::setFingerPosition(1, location.x, location.y, true);
	}
}


- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event 
{	
	UITouch *current_touch = [touches anyObject];
	
	NSSet *allTouches = [event allTouches];
	int i, len=[allTouches count];
	
	//	NSLog(@"touchesEnded %d", len);
	
	for(i=0 ; i<len ; i++) 
	{
		UITouch *touch = [[allTouches allObjects] objectAtIndex:i];
		if(touch == current_touch) {
			CGPoint location = [touch locationInView:self];
			KInput::setFingerPosition(i, location.x, location.y, false);
			//		NSLog(@"KInput::setFingerPosition %d (%d %d) false", i, (int)location.x, (int)location.y);
			if(i==0) {
				KInput::swapFingerPosition(0, 1);
			}
		}
	}
	KInput::setScreenReleased();
}

// Implement this method to get the lastest data from the accelerometer 
- (void)accelerometer:(UIAccelerometer*)accelerometer didAccelerate:(UIAcceleration*)acceleration 
{
	//Use a basic low-pass filter to only keep the gravity in the accelerometer values
	_accelerometer[0] = acceleration.x * kFilteringFactor + _accelerometer[0] * (1.0 - kFilteringFactor);
	_accelerometer[1] = acceleration.y * kFilteringFactor + _accelerometer[1] * (1.0 - kFilteringFactor);
	_accelerometer[2] = acceleration.z * kFilteringFactor + _accelerometer[2] * (1.0 - kFilteringFactor);
	KInput::setAccelerometer(_accelerometer[0], _accelerometer[1], _accelerometer[2]);
}



@end
