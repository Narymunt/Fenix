// konfiguracja ekranu urzadzenia
// SDS = soft def. square = dla rozdzielczosci <1500px przy pixel ratio < 1.5 (kwadratowe, np. 1024x768)
// SDW = soft def. wide = dla rozdzielczosci <1500px przy pixel ratio >1.5 (szerokie np. 1366x768, 1280x600)
// HDS = high def. square = dla rozdzielczosci >=1500px przy pixel ratio >1.5 (kwadratowe np. 2048x1536)
// HDW = high def. square = dla rozdzielczosci >=1500px przy pidel ratio > 1.5 (szerowkie np. 1920x1080)
//
// rozdzielczosci bazowe
// SDS - 1024x768
// SDW - 1366x768
// HDS - 2048x1536
// HDW - 1920x1080

#pragma once

#include <vector>
#include "SDL.h"
#include "OGL.h"


class CScreen
{

public : 

	CScreen();								// init screen with desktop resolution
	~CScreen();

	void			Clear(void);
	void			Flip(void);

public:
    
    SDL_DisplayMode		_mode;
    SDL_Window			*_window;
    SDL_GLContext		_gl;

    int					_iSizeX, _iSizeY;					// aktualne wspolrzedne ekranu
    bool				_isSDS, _isSDW, _isHDS, _isHDW;		// jaki typ rozdzielczosci
    float				_fPixelRatio, _fReverseRatio;

    unsigned int        _iGridX[101];						// siatka w procentach
    unsigned int        _iGridY[101];

};


