/*
 *  KPTK.h
 *  JDK
 *
 *  Created by Julien meyer on 04/05/08.
 *  Copyright 2010 jmApp.com All rights reserved.
 *
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
	
	K_320x480,
	K_480x320,
	
	
	// IPAD
	
	K_768x1024,
	K_1024x768
};



class KPTK
{

public:	
	static	screenOrientation	_screenOrientation ;
	
	static KWindow		* createKWindow(screenOrientation orientation);
	static KGraphic		* createKGraphic();
	static KBatch		* createKBatch();
//	static int			getWindowWidth();
//	static int			getWindowHeight();
};


#endif // API_KPTK__

