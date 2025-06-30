#include "KGraphicGL.h"
#include "KGraphicGLLandscape.h"
#include "KWindow.h"

#include <UIKit/UIKit.h>


KWindow::KWindow()
{
	setClearColor( 1,1,1,1 ) ;
	_terminated = false ;
	
}

void KWindow::setClearColor( float r, float g , float b, float a ) 
{
	_red = r ;
	_green = g ;
	_blue = b ;
	_a = a ;
}

int KWindow::iX(void)
{
    int x =[ [ UIScreen mainScreen ] bounds ].size.height;
    return x;
}

int KWindow::iY(void)
{
    int y = [ [ UIScreen mainScreen ] bounds ].size.width;
    return y;
}

float KWindow::fScale(void)
{
    float screenScale = [[UIScreen mainScreen] scale];
    return screenScale;
}

bool KWindow::createGameWindow(int w, int h, int bpp, bool windowed, char *name)
{
	window_width = w;
	window_height = h;
    
	return true;
}

void KWindow::setTitle(char *title)
{
}

int KWindow::getWindowWidth()
{
	return window_width;
}

int KWindow::getWindowHeight()
{
	return window_height;
}

int KWindow::getWindowHandle()
{
	return 0;
}

void KWindow::setMaxFrameRate(int maxFps)
{

}

void KWindow::terminate( void ) 
{
	_terminated = true ;
}

void KWindow::setWorldView(float tranX , float transY , float angle, float zoom, bool clearworld )
{
	/*glDisable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);	
	if ( clearworld == true )
	{
		glClearColor( _red , _green , _blue , _a) ;
		glClear(GL_COLOR_BUFFER_BIT);	
	}
	glLoadIdentity();
	//glOrthof(0, 320 ,0, 480 , -100 , 100 );
	glOrthof(0, window_width ,0, window_height , -100 , 100 );*/
}

void KWindow::setDefaultWorldView()
{
	glClearColor( _red, _green, _blue, _a );
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);	
	glClear(GL_COLOR_BUFFER_BIT);	
	glLoadIdentity();
	glOrthof(0, window_width ,0, window_height , -100 , 100 );
//	glOrthof(0, window_width*2, 0, window_height*2, -100, 100);
}

void KWindow::flipBackBuffer()
{
	//swapBuffers();
}

bool KWindow::isQuit()
{
	return _terminated ;
}


