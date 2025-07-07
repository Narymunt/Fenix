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
#include "OGL.h"
#include "../../Game.h"
#include "SpriteObject.h"

class CScreen
{

public : 

	CScreen(int iX, int iY, int iBpp,bool bFullScreen);		// window init
	CScreen(bool bFullScreen);								// init screen with desktop resolution
	~CScreen();

	void InitDictionary(void);	// wczytaj nazwy plikow dla wszystkich obiektów 

	void Precalc(void);		// prepare precalc tables

   inline int	iSizeX(void) { return _iSizeX; }
   inline int	iSizeY(void) { return _iSizeY; }
   inline int	iBpp(void) { return _iBpp; }
   inline bool isFullscreen(void) { return _bFullscreen; }

	float fPixelX(void);		// X pixel size
	float fPixelY(void);		// y pixel size

	char	*pArg(int iParam);	// zwraca nazwe dla danego numeru parametru
	int		iArg(int iParam);	// zwraca liczbe calkowita dla danego numeru parametru
	float	fArg(int iParam);	// zwraca liczbe rzeczywista dla danego numeru parametru

	// dla slownika

	bool	isSpriteObject(char cName[]);
	char	*cObjectFilename(char cName[]);		// zwroc nazwe pliku dla poszukiwanego obiektu
	
	float	fRotation(char cName[]);			// zwroc rotacje dla poszukiwanego obiektu
	float	fRotationI(char cName[]);

	float	fPositionX(char cName[]);
	float	fPositionXI(char cName[]);
	
	float	fPositionY(char cName[]);
	float	fPositionYI(char cName[]);

	float	fScaleX(char cName[]);
	float	fScaleXI(char cName[]);

	float	fScaleY(char cName[]);
	float	fScaleYI(char cName[]);

	float	fAlfa(char cName[]);
	float	fAlfaI(char cName[]);

	bool	isCenter(char cName[]);

	inline bool isSDS(void) { return _isSDS; }
	inline bool isSDW(void) { return _isSDW; }
	inline bool isHDS(void) { return _isHDS; }
	inline bool isHDW(void) { return _isHDW; }

   inline int xSDS(int i) { return _iXTableSDS[i]; }
   inline int ySDS(int i) { return _iYTableSDS[i]; }

   inline int xSDW(int i) { return _iXTableSDW[i]; }
   inline int ySDW(int i) { return _iYTableSDW[i]; }

   inline int xHDS(int i) { return _iXTableHDS[i]; }
   inline int yHDS(int i) { return _iYTableHDS[i]; }

   inline int xHDW(int i) { return _iXTableHDW[i]; }
   inline int yHDW(int i) { return _iYTableHDW[i]; }

   int getX(int x);  // autodetekcja aktualnej rozdzielczosci i tablicy przeliczeniowej
   int getY(int y);  // podaje zwrotny parametr dla podanego pixela, samemu trzeba pamietac o limitach

protected :

	char	_buffer[256];		// uzywamy do generowania nazw

	bool	_bFullscreen;

	bool	_isSDS, _isSDW, _isHDS, _isHDW;	

	int		_iSizeX, _iSizeY, _iBpp;

	int		_iXTableHDW[1920];
	int		_iYTableHDW[1080];

	int		_iXTableHDS[2048];
	int		_iYTableHDS[1536];

   int      _iXTableSDS[1024];
   int      _iYTableSDS[768];

   int      _iXTableSDW[1366];
   int      _iYTableSDW[768];

	float	_fPixelX, _fPixelY;

private :

	std::vector <CSpriteObject*>	_pDict;		// nasz slownik

};


