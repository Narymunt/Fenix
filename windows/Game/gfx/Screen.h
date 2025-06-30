#pragma once

#include <SDL.h>
#include <vector>
#include "../gfx/OGL.h"
#include "../Game.h"

class CScreen
{

public : 
	
	CScreen();											// fullscreen, rozdzielczosc taka sama jak desktop
	CScreen(int x, int y, bool fullscreen);				// okno lub fullscreen o podanym wymiarze

	~CScreen() {};

	inline int x(int x) { return (int)((float)x * _sizePixelX); };
	inline int y(int y) { return (int)((float)y * _sizePixelY); };			// podaje zwrotny parametr dla podanego pixela, samemu trzeba pamietac o limitach

	bool	_fullscreen;
	int		_sizeX, _sizeY;

	int		_x[1920], _y[1080]; // ta tablica jest do wskazywania miejsca
	int		* _targetX, *_targetY;

	float	_sizePixelX, _sizePixelY;
	float   _revPixelX, _revPixelY;

	float	_aspectRatio, _reverseRatio;		// czy rozdzielczosc jest kwadratowa czy szeroka

	bool	_isHD, _isWide;

private :

	void	init(int x, int y, bool fullscreen);

	void	precalc(void);		// prepare precalc tables

};


