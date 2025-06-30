/**
   SpriteObject.h
   SpriteObject trzymamy po to, aby przyspieszyc wczytywanie pliku.
   Zawiera wszystkie informacje o obiekcie, ale nie posiada tekstury do renderowania.

   @author Jaros³aw Ro¿yñski   
*/

#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "../gfx/OGL.h"
#include "../gfx/Screen.h"
		
class CSpriteObject
{

public:

	CSpriteObject();												// najpierw uruchomiony jest ten konstruktor, a potem od sprite
	~CSpriteObject();

	// do porownywania nazw

	bool				isName(char name[]);

	void				position(float x, float y);					// set & get position
	void				scale(float fX, float fY);					// set & get scale 
	void				scale(float s);								// ustawia dla X & Y
	void				color(float r, float g, float b, float a);	// ustaw kolor
	void				pivot(float x, float y);					// punkt obrotu / skali

	void				scaleI(float x, float y);					// modyfikatory dla skali
	void				scaleI(float s);							// ustawia dla X & Y
	void				positionI(float x, float y);				// modyfikator dla wspó³rzêdnych
	void				colorI(float r, float g, float b, float a);	// modifikator koloru

	void				resize(int x1, int y1, int x2, int y2);		// rozmiar na podstawie wspolrzednych ekranu
	void				fullscreen(CScreen *screen);				// zmien rozmiar na taki sam jak rozmiar okna renderowania

	// modyfikator dla kana³u alfa

	bool				_isCenter;									// false = lewy gorny rog, true = srodek tekstury
	float				_sizeX, _sizeY;								// aktualny rozmiar sprite, rozmiar = orygina³ * skala
	float				_rotation;									// aktualny k¹t obrotu
	float				_originalX, _originalY;						// oryginalne wymiary
	float				_scaleX, _scaleY;							// skala, 1.0 = orygina³
	float				_x, _y;										// pozycje na ekranie
	float				_pivotX, _pivotY;							// punkt obrotu, dla isCenter = 0.5f
	float				_r, _g, _b, _a;

	unsigned long		_renderTime;								// czas renderowania ostatniej klatki
	unsigned long		_deltaTime;									// roznica pomiedzy ostatnim renderowaniem a aktualnym timerem

	// incrementators, how much do we want to add per rendered frame

	float				_rotationI;
	float				_scaleXI, _scaleYI;
	float				_xI, _yI;
	float				_rI, _gI, _bI, _aI;

	char				_objectName[256];	// nazwa naszego obiektu
	char				_filename[256];		// nazwa pliku

};

 