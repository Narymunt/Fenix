/*
 *  KWindow.h
 *
 *  Created by Julien meyer on 04/05/08.
 *  Copyright 2010 jmApp.com All rights reserved.
 *
 */

#ifndef API_KWINDOW__
#define API_KWINDOW__

#include <stdio.h>
#include <stdlib.h>


class KWindow
{
private:
	int		window_width;
	int		window_height;
	float  _red,_green , _blue , _a ;
	bool	_terminated ;
	
public:
		
	KWindow();
		
	bool	createGameWindow(int w, int h, int bpp, bool windowed, char *name);
	void	setTitle(char *title);
	int		getWindowWidth();
	int		getWindowHeight();
	int		getWindowHandle();
	void	setMaxFrameRate(int maxFps);
	void	setDefaultWorldView();
	void	flipBackBuffer();
	bool	isQuit();
	void	setClearColor( float r, float g , float b, float a ) ;
	
	void	setWorldView(float tranX , float transY , float angle, float zoom, bool clearworld ) ;
	void	terminate( void ) ;

	
};

#endif // API_KWINDOW__

