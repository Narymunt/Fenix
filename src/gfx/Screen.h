/**
   Screen.h 

   screen pelni rowniez role slownika, w ktorym zapisane sa informacje o wszystkich nazwach pliku dla danej rozdzielczosci
   dzieki temu nie musimy za kazdym razem przeszukiwac skryptu w poszukiwaniu sprite'a, ale grzebiemy tylko w slowniku, ktory jest
   zaladowany do pamieci i dzieki temu calosc trwa o wiele szybciej

   tablice przeliczeniowe u¿ywane do wymiarowania
*/

#pragma once

#include <SDL.h>
#include <vector>
#include "../gfx/OGL.h"
#include "../Game.h"

class CScreen
{

public : 
	
	CScreen();	// fullscreen
	CScreen(bool isFullscreen);
	CScreen(int x, int y);
	CScreen(int x, int y, bool isFullscreen);				// okno o podanym wymiarze
	~CScreen();

	float	pixelX(void);		// X pixel size
	float	pixelY(void);		// y pixel size

	int		x(int x);			// autodetekcja aktualnej rozdzielczosci i tablicy przeliczeniowej
	int		y(int y);			// podaje zwrotny parametr dla podanego pixela, samemu trzeba pamietac o limitach

	int		perX(float f);		// wspó³rzêdne ekranu w skali 0.0f-100.0f
	int		perY(float f);		// to operuje na rzeczywistych wymiarach ekranu

	bool	_isFullscreen;

	bool	_isSDS, _isSDW, _isHDS, _isHDW;	

	int		_sizeX, _sizeY;

	int		_xHDW[1920], _yHDW[1080];
	int		_xHDS[2048], _yHDS[1536];
	int     _xSDS[1024], _ySDS[768];
	int     _xSDW[1366], _ySDW[768];

	float	_pixelX, _pixelY;

private :

	void	init(int x, int y, bool isFullscreen);
	void	precalc(void);		// prepare precalc tables
	void	precalcTable(int size, int *table);	// pomocnicza


};


