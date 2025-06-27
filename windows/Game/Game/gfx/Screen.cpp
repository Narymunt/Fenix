#pragma warning(disable : 4996)
#pragma warning(disable : 4715)

#include "Screen.h"

CScreen::CScreen() :
_isSDS(false), _isSDW(false), _isHDS(false), _isHDW(false),
_sizeX(0), _sizeY(0), _isFullscreen(true)
{
	init(0, 0, true);
}

CScreen::CScreen(bool isFullscreen) :
_isSDS(false), _isSDW(false), _isHDS(false), _isHDW(false),
_sizeX(0), _sizeY(0), _isFullscreen(true)
{
	init(0, 0, isFullscreen);
}

CScreen::CScreen(int x, int y) :
_isSDS(false), _isSDW(false), _isHDS(false), _isHDW(false),
_sizeX(0), _sizeY(0), _isFullscreen(true)
{
	init(x, y, true);
}

CScreen::CScreen(int x, int y, bool isFullscreen) :
_isSDS(false), _isSDW(false), _isHDS(false), _isHDW(false),
_sizeX(0), _sizeY(0), _isFullscreen(true)
{
	init(x, y, isFullscreen);
}


void CScreen::init(int x, int y, bool fullscreen)
{
	const SDL_VideoInfo	*pVideoInfo;
	float pixelRatio, reverseRatio;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return;

	pVideoInfo = SDL_GetVideoInfo();

	if (x == 0 && y == 0 )
	{
		x = pVideoInfo->current_w;
		y = pVideoInfo->current_h;

		if (!fullscreen)	// jezeli podalismy bez x,y oraz fullscreen false to ustawiamy okno po³owy rozmiaru ekranu
		{
			x /= 2; y /= 2;
		}
	}

	if (fullscreen)
	{
		oglInit(x, y, 32, SDL_FULLSCREEN);
	}
	else
	{
		oglInit(x, y, 32, 0);
	}

	_sizeX = x; _sizeY = y; 
	_isFullscreen = fullscreen;
	pixelRatio = (float)_sizeX / (float)_sizeY;
	reverseRatio = (float)_sizeY / (float)_sizeX;
	printf("[SCREEN]: %dx%d | pixelRatio %f | reverseRatio %f | ", x, y, pixelRatio, reverseRatio);

	if (_sizeX < 1500)
	{
		if (pixelRatio > reverseRatio) 
		{
			(pixelRatio < 1.5f) ? _isSDS = true : _isSDW = true;
		}
		else
		{
			(reverseRatio < 1.5f) ? _isSDS = true : _isSDW = true;
		}
	}
	else
	{
		if (pixelRatio > reverseRatio)
		{
			(pixelRatio < 1.5f) ? _isHDS = true : _isHDW = true;
		}
		else
		{
			(reverseRatio < 1.5f) ? _isHDS = true : _isHDW = true;
		}
	}

	if (_isSDS) printf("[SDS]\n");
	if (_isSDW) printf("[SDW]\n");
	if (_isHDS) printf("[HDS]\n");
	if (_isHDW) printf("[HDW]\n");

	precalc();

}

CScreen::~CScreen() { }

/** 
   Przygotuj tablice przeliczeniowe.
*/

void CScreen::precalcTable(int size, int *table)
{
	float index, pixelSize;
	
	index = 0; pixelSize = _sizeX / (float)size; _pixelX = pixelSize;

	for (int i = 0; i<size; i++)
	{
		table[i] = (int)index;
		index += pixelSize;
	}
}

void CScreen::precalc(void)
{
	precalcTable(1920, _xHDW); precalcTable(1080, _yHDW);
	precalcTable(2048, _xHDS); precalcTable(1536, _yHDS);
	precalcTable(1366, _xSDW); precalcTable(768, _ySDW);
	precalcTable(1024, _xHDS); precalcTable(768, _ySDS);
}

/**
   Zwraca rozmiar pixela.
   @return rozmiar ekranu / aktualne wymiary zrodlowe
*/

float CScreen::pixelX(void)
{
   if (_isSDS) return (float)_sizeX/1024.0f;
   if (_isSDW) return (float)_sizeX/1366.0f;
   if (_isHDS) return (float)_sizeX/2048.0f;   
   if (_isHDW) return (float)_sizeX/1920.0f;
}

/**
   Zwraca rozmiar pixela.
   @return rozmiar ekranu / aktualne wymiary zrodlowe
*/

float CScreen::pixelY(void)
{
   if (_isSDS) return (float)_sizeX/1024.0f;
   if (_isSDW) return (float)_sizeX/1366.0f;
   if (_isHDS) return (float)_sizeX/2048.0f;
   if (_isHDW) return (float)_sizeX/1920.0f;

}

/**
   Zwraca rzeczywist¹ wspó³rzêdn¹ na ekranie, gdy operujemy na fikcyjnych liczbach.
   @param x gdzie na ekranie chcemy postawiæ pixel
   @return gdzie naprawde postawimy pixel
*/

int CScreen::x(int x)
{
   if (_isSDS) return _xSDS[x];
   if (_isSDW) return _xSDW[x];
   if (_isHDS) return _xHDS[x];
   if (_isHDW) return _xHDW[x];
}

/**
   Zwraca rzeczywist¹ wspó³rzêdn¹ na ekranie, gdy operujemy na fikcyjnych liczbach.
   @param y gdzie na ekranie chcemy postawiæ pixel
   @return gdzie naprawde postawimy pixel
*/

int CScreen::y(int y)
{
   if (_isSDS) return _ySDS[y];
   if (_isSDW) return _ySDW[y];
   if (_isHDS) return _yHDS[y];
   if (_isHDW) return _yHDW[y];
}

int CScreen::perX(float f)
{ 
	float x; 
	x = (float)_sizeX *(100.0f / f);
	return (int)x;
}

int CScreen::perY(float f)
{
	float y;
	y = (float)_sizeY *(100.0f / f);
	return (int)y;
}

