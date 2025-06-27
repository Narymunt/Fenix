// Released under MIT License
/*
 Copyright (c) 2010 by Julien Meyer. Web: http://www.jmApp.com
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */


#include "KLogFile.h"
#include "KInput.h"
#include	"KPTK.h"

bool	KInput::_screenPressed = false;
int		KInput::_xScreenHit = 0;
int		KInput::_yScreenHit = 0;
int		KInput::_tapeCount = 0;
int		KInput::midX = 0;
int		KInput::midY = 0;
float	KInput::_xAcc = 0;
float	KInput::_yAcc = 0;
float	KInput::_zAcc = 0;

bool	KInput::_btPressed = ISUP;
long	KInput::_mx=0,KInput::_my =0;

sFinger	KInput::finger[2] = { 0,0,false ,0,0,false} ;

void KInput::initInput(int windowHandle) 
{
	_screenPressed = false;
}

void KInput::hidePointer()
{
}

sFinger	*KInput::getFinger( short fingerid )
{
	if ( fingerid >1 ) return 0 ;
	return &finger[fingerid] ;
	
}

void	KInput::setFingerPosition( int fingerid , short	x , short y , bool pressed ) 
{
	if( fingerid > 1 ) return;

	finger[fingerid].pressed = pressed ;

	if( KPTK::_screenOrientation == K_320x480 || KPTK::_screenOrientation == K_768x1024) {
		finger[fingerid].x = x ;
	}
	else if(KPTK::_screenOrientation == K_480x320) {
		finger[fingerid].x = 480-y;
	}	
	else if(KPTK::_screenOrientation == K_1024x768) {
		finger[fingerid].x = 1024-y;
	}	
	
	if( KPTK::_screenOrientation == K_320x480 || KPTK::_screenOrientation == K_768x1024) {
		finger[fingerid].y = y;
	}
	else {
		finger[fingerid].y = x;
	}
}

void	KInput::swapFingerPosition(int fingerid1, int fingerid2) 
{
	if( fingerid1 > 1 ) return;
	if( fingerid2 > 1 ) return;
	
	short x_ = finger[fingerid1].x;
	finger[fingerid1].x = finger[fingerid2].x;
	finger[fingerid2].x = x_;
	
	short y_ = finger[fingerid1].y;
	finger[fingerid1].y = finger[fingerid2].y;
	finger[fingerid2].y = y_;
	
	bool p_ = finger[fingerid1].pressed;
	finger[fingerid1].pressed = finger[fingerid2].pressed;
	finger[fingerid2].pressed = p_;
}

bool KInput::isPressed(int keyCode)
{
	return _btPressed;
	/*
	if(keyCode == K_VK_ESCAPE) {
		return ISUP;
	}
	return _screenPressed; //ISUP;
	*/
}

void KInput::mousePointerTo(int x, int y)
{
//	KLogFile::logDebug("mousePointerTo: %d %d", x, y);
	midX = x;
	midY = y;
}

int KInput::getMouseX()
{
	if( KPTK::_screenOrientation == K_320x480 || KPTK::_screenOrientation == K_768x1024 )
	{
	   return (int)_xScreenHit;// - midX;
	}
	if( KPTK::_screenOrientation == K_480x320) {
		return (int)480-_yScreenHit;// - midX;		
	}
	else if( KPTK::_screenOrientation == K_1024x768) {
		return (int)1024-_yScreenHit;// - midX;		
	}
	return 0;
}

int KInput::getMouseY()
{
	if( KPTK::_screenOrientation == K_320x480 || KPTK::_screenOrientation == K_768x1024 )
	{
		return (int)_yScreenHit;// - midX;
	}
	return (int)_xScreenHit;// - midX;
}

bool KInput::getLeftButtonState()
{
	return _btPressed;
}

void KInput::showPointer()
{
}


// iphone specific events calls

float KInput::getAccelerationX()
{
	return _xAcc;
}

float KInput::getAccelerationY()
{
	return _yAcc;
}

float KInput::getAccelerationZ()
{
	return _zAcc;
}

void KInput::setAccelerometer(float x, float y, float z)
{
	//printf("%f %f %f\n", x, y, z);
	_xAcc = x;
	_yAcc = y;
	_zAcc = z;
}

int KInput::getScreenTap()
{
	return _tapeCount;
}

bool KInput::isScreenPressed(int *hitX, int *hitY)
{
	if(_screenPressed == false) {
		_btPressed = ISUP ;
		return false;
	}
	
	_btPressed = ISDOWN ;
	
    if(hitX) {
		*hitX = KInput::getMouseX();
	}
	if(hitY) {
		*hitY = KInput::getMouseY();
	}
	//KLogFile::logDebug("setScreenMoving: %d %d", *hitX, *hitY);
	return true;
}

bool KInput::isScreenReleased(int *hitX, int *hitY)
{
	if(_screenPressed == true) {
		return false;
	}
    if(hitX) {
		*hitX = KInput::getMouseX();
	}
	if(hitY) {
		*hitY = KInput::getMouseY();
	}	
	return true;
}

void KInput::setScreenPressed(int tapCount, int x, int y)
{
	//printf("setScreenPressed: %d %d\n", x, y);
	_btPressed = ISDOWN ;
	_screenPressed = true;
	_xScreenHit = x;
	_yScreenHit = y;
	_tapeCount = tapCount;
}

void KInput::setScreenMoving(int x, int y)
{
	//printf("setScreenMoving: %d %d\n", x, y);
	_xScreenHit = x;
	_yScreenHit = y;
}

void KInput::setScreenReleased()
{
	//printf("setScreenReleased\n");
	_screenPressed = false;
	_btPressed = ISUP ;
	//_xScreenHit = -1;
	//_yScreenHit = -1;
	_tapeCount = 0;
}








