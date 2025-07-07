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


#include "KPTK.h"
#include "KGraphic.h"
#include "KGraphicGL.h"
#include "KGraphicGLLandscape.h"
#include "KLogFile.h"

#include "KWindow.h"

screenOrientation	KPTK::_screenOrientation ;


KWindow * KPTK::createKWindow(screenOrientation orientation)
{
	_screenOrientation = orientation ;
	KWindow *ptk_Window = new KWindow();
	return ptk_Window;
}


KGraphic * KPTK::createKGraphic()
{

	if( _screenOrientation == IPHONE_1136x640 )
	{
		KGraphicGLLAND  *kgll ;
		kgll = new KGraphicGLLAND(1136, 640);
		return kgll ;
	}

	if( _screenOrientation == IPHONE_960x640 )
	{
		KGraphicGLLAND  *kgll ;
		kgll = new KGraphicGLLAND(960, 640);
		return kgll ;
	}
    
	if( _screenOrientation == IPAD_1024x768 )
	{
		KGraphicGLLAND  *kgll ;
		kgll = new KGraphicGLLAND(1024, 768);
		return kgll ;
	}

	if( _screenOrientation == IPAD_2048x1536)
	{
		KGraphicGLLAND  *kgll ;
		kgll = new KGraphicGLLAND(2048, 1536);
		return kgll ;
	}
    
	return 0;
}

KGraphic * KPTK::create(int x, int y)
{
		KGraphicGLLAND  *kgll ;
		kgll = new KGraphicGLLAND(x,y);
		return kgll ;
}


KBatch * KPTK::createKBatch()
{

	if ( _screenOrientation == IPHONE_960x640 )
	{
		KBatch  *kgll ;
		kgll = new KBatch(960, 640);
		return kgll ;
	}

	if ( _screenOrientation == IPHONE_1136x640 )
	{
		KBatch  *kgll ;
		kgll = new KBatch(1136, 640);
		return kgll ;
	}
    
	if ( _screenOrientation == IPAD_2048x1536 )
	{
		KBatch  *kgll ;
		kgll = new KBatch(2048, 1536);
		return kgll ;
	}
    
	if ( _screenOrientation == IPAD_1024x768 )
	{
		KBatch  *kgll ;
		kgll = new KBatch(1024, 768);
		return kgll ;
	}
    
	return 0;
}

