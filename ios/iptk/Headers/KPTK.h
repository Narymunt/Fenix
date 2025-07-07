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

#ifndef API_KPTK__
#define API_KPTK__

#include <stdio.h>
#include <stdlib.h>

//#include "KMiscTools.h"
//#include "KLogFile.h"
#include "KWindow.h"
#include "KGraphic.h"
//#include "KInput.h"
#include	"KBatch.h"


#define	PTK_FREEPTR(x)   if(x)  { delete x ; x = NULL ; }

enum screenOrientation
{
	// IPHONE
    
	IPHONE_320x480,
	IPHONE_480x320,

    // iPhone retina
    
    IPHONE_960x640,
    IPHONE_1136x640,
	
	// IPAD
	
	IPAD_1024x768,
    IPAD_2048x1536
};



class KPTK
{

public:	
	static	screenOrientation	_screenOrientation ;
	
	static KWindow		* createKWindow(screenOrientation orientation);
	static KGraphic		* createKGraphic();
    static KGraphic     * create(int x, int y);
	static KBatch		* createKBatch();
};


#endif // API_KPTK__

