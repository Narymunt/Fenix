// screen class, you can use more than one screen

// WINDOWS :
// @1920 - 1920x1080 is a native HD resolution, pixel size 1.7
// @1366 - 1366x768 is 19.28% most common screen resolution, pixel size 1.7
// @1280 - 1280x800 is 13%, pixel size 1.6
// @1024 - 1024x768 pixel size 1.4 

// MAC : 
// @1920 
// @1366
// @1024

// ANDROID : 
// @1920
// @1366
// @1024 - 1024x768
// @800 - 1280x800
// @600 - 1280x600
// @720 - 1280x720
// @400 - 800x480

// iOS :
// @320 - 320x480
// @640 - 640x960
// @1136 - 1136x640
// @1024 - 1024x768
// @2048 - 2048x1536

// i'm using 1920x1080 as reference, using screen conversion to get actual screen position
// xtable && ytable is for optimization - use index to avoid mul and div per frame

#pragma once

#include <SDL.h>
#include "OGL.h"
#include "Game.h"

class CScreen
{

public : 

	CScreen(int iX, int iY, int iBpp,bool bFullScreen);		// window init
	CScreen(bool bFullScreen);								// init screen with desktop resolution
	~CScreen();

	void Precalc(void);		// prepare precalc tables

	int	iSizeX(void);
	int	iSizeY(void);
	int	iBpp(void);
	bool isFullscreen(void);

	int	toX(int x);
	int	toY(int y);

	float fPixelX(void);		// X pixel size
	void fPixelX(float f);

	float fPixelY(void);		// y pixel size
	void fPixelY(float f);		

	char	*pArg(int iParam);	// zwraca nazwe dla danego numeru parametru
	int		iArg(int iParam);	// zwraca liczbe calkowita dla danego numeru parametru
	float	fArg(int iParam);	// zwraca liczbe rzeczywista dla danego numeru parametru

protected :

	char	_buffer[256];		// uzywamy do generowania nazw

	bool	_bFullscreen;

	int		_iSizeX, _iSizeY, _iBpp;

	int		_iXTable[1921];
	int		_iYTable[1081];

	float	_fPixelX, _fPixelY;
};


