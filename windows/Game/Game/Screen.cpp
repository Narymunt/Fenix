#include "Screen.h"

#pragma warning(disable : 4996)

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

// po kolei wybieramy najlepsze rozdzielczosci pelnoekranowe
// w koncu gdy nie uda sie ustalic zadnej, to ustawiamy rozdzielczosc biurka

CScreen::CScreen(bool bFullScreen)
{
	const	SDL_VideoInfo	*pVideoInfo;

	_iSizeX = _iSizeY = 0;

	if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) 
	return ;

	// iPad HD

	if (oglInit(2048,1536,32,SDL_FULLSCREEN))
	{
		_iSizeX = 2048;
		_iSizeY = 1536;
		_bFullscreen = true;
		_iBpp = 32;
		return;
	}


	// iMac 27"

	if (oglInit(2048,1440,32,SDL_FULLSCREEN))
	{
		_iSizeX = 2048;
		_iSizeY = 1440;
		_bFullscreen = true;
		_iBpp = 32;
		return;
	}

	// HD

	if (oglInit(1920,1080,32,SDL_FULLSCREEN))
	{
		_iSizeX = 1920;
		_iSizeY = 1080;
		_bFullscreen = true;
		_iBpp = 32;
		return;
	}

	// half HD

	if (oglInit(1366,768,32,SDL_FULLSCREEN))
	{
		_iSizeX = 1366;
		_iSizeY = 768;
		_bFullscreen = true;
		_iBpp = 32;
		return;
	}


	// 1024x768

	if (oglInit(1024,768,32,SDL_FULLSCREEN))
	{
		_iSizeX = 1024;
		_iSizeY = 768;
		_bFullscreen = true;
		_iBpp = 32;
		return;
	}


	// poddaje sie - ustawiam rozdzielczosc biurka

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

// zwraca nazwe dla danego numeru parametru
 
char *CScreen::pArg(int iParam)
{
	return _buffer;
}

// zwraca liczbe calkowita dla danego numeru parametru

int CScreen::iArg(int iParam)
{
	return 0;
}

// zwraca liczbe rzeczywista dla danego numeru parametru

float CScreen::fArg(int iParam)
{
	return 0.f;
}