#pragma warning(disable : 4996)
#pragma warning(disable : 4715)

#include "Screen.h"

CScreen::CScreen() :
_sizeX(0), _sizeY(0), _fullscreen(true)
{
	init(0, 0, true);
}

CScreen::CScreen(int x, int y, bool fullscreen) :
_sizeX(0), _sizeY(0), _fullscreen(true)
{
	init(x, y, fullscreen);
}

void CScreen::init(int x, int y, bool fullscreen)
{
	const SDL_VideoInfo	*pVideoInfo;

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

	fullscreen ? oglInit(x, y, 32, SDL_FULLSCREEN) : oglInit(x, y, 32, 0);

	_sizeX = x; _sizeY = y; 
	_fullscreen = fullscreen;
	
	_aspectRatio = (float)_sizeX / (float)_sizeY;	
	_reverseRatio = (float)_sizeY / (float)_sizeX;
	
	printf("[SCREEN]: %dx%d | pixelRatio %f | reverseRatio %f | ", x, y, _aspectRatio, _reverseRatio);

	if (_sizeX < 1500)
	{
		if (_aspectRatio > _reverseRatio) 
		{
			(_aspectRatio < 1.5f) ? _isWide = false : _isWide = true;
		}
		else
		{
			(_reverseRatio < 1.5f) ? _isWide = false : _isWide = true;
		}
	}
	else
	{
		if (_aspectRatio > _reverseRatio)
		{
			(_aspectRatio < 1.5f) ? _isWide = false : _isWide = true;
		}
		else
		{
			(_reverseRatio < 1.5f) ? _isWide = false : _isWide = true;
		}
	}

	_isWide ? printf("\nWIDE: YES ") : printf("\nWIDE: NO ");
	_isHD ? printf("HD: YES ") : printf("HD: NO ");

	precalc();

}

void CScreen::precalc(void)
{
	_sizePixelX =  (float)_sizeX / 1920.0f;
	_sizePixelY =  (float)_sizeY / 1080.0f;

	_revPixelX = 1920.0f / (float)_sizeX;
	_revPixelY = 1080.0f / (float)_sizeY;

	for (int x = 0; x != 1920; x++)
		_x[x] = _sizePixelX * x;

	for (int y = 0; y != 1080; y++)
		_y[y] = _sizePixelY * y;

}

