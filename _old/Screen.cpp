#include "Screen.h"

CScreen::CScreen(int iX, int iY, int iBpp,bool bFullScreen)
{

	if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) 
	return ;

	if (bFullScreen)
	{
		oglInit(iX, iY, iBpp, SDL_FULLSCREEN);
	}
	else
	{
		oglInit(iX, iY, iBpp, 0);
	}

	_iSizeX = iX;
	_iSizeY = iY;
	_iBpp = iBpp;
	_bFullscreen = bFullScreen;
	Precalc();
}

CScreen::CScreen(bool bFullScreen)
{
	const	SDL_VideoInfo	*pVideoInfo;

	_iSizeX = _iSizeY = 0;

	if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) 
	return ;

	pVideoInfo = SDL_GetVideoInfo();

	_iSizeX = pVideoInfo->current_w;
	_iSizeY = pVideoInfo->current_h;
	_bFullscreen = bFullScreen;
	_iBpp = 32;

	if (bFullScreen)
	{
		oglInit(_iSizeX, _iSizeY, _iBpp, SDL_FULLSCREEN);
	}
	else
	{
		_iSizeX /=2 ; _iSizeY/=2;

		oglInit(_iSizeX, _iSizeY, _iBpp, 0);
	}

	Precalc();
}

CScreen::~CScreen()
{

}

int CScreen::iBpp(void)
{
	return _iBpp;
}

int CScreen::iSizeX(void)
{
	return _iSizeX;
}

int CScreen::iSizeY(void)
{
	return _iSizeY;
}

bool CScreen::isFullscreen(void)
{
	return _bFullscreen;
}

void CScreen::Precalc(void)
{
	float fIndex, fPixelSize;

	fIndex = 0;
	fPixelSize =  _iSizeX / 1920.0f  ;
	_fPixelX = fPixelSize;

	for (int i=0; i<1921; i++)
	{
		_iXTable[i] = (int)fIndex;
		fIndex += fPixelSize;
	}

	fIndex = 0;
	fPixelSize = _iSizeY / 1080.0f;
	_fPixelY = fPixelSize;

	for (int i=0; i<1081; i++)
	{
		_iYTable[i] = (int)fIndex;
		fIndex += fPixelSize;
	}

	printf("pixel size : %f x %f\n", _fPixelX, _fPixelY);
}

int CScreen::toX(int x)
{
	return _iXTable[x];
}

int CScreen::toY(int y)
{
	return _iYTable[y];
}

void CScreen::fPixelX(float f)
{
	_fPixelX = f;
}

float CScreen::fPixelX(void)
{
	return _fPixelX;
}

void CScreen::fPixelY(float f)
{
	_fPixelY = f;
}

float CScreen::fPixelY(void)
{
	return _fPixelY;
}
