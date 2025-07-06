/**
   Sprite.h
   Sprite zawiera jedn� tekstur� wraz z parametrami. 
   Mo�e by� inicjalizowany ze skryptu lub r�cznie. 

   Struktura wpisu w skrypcie :
   <SPRITE>
   [nazwa_obiektu]
   [ekranX] 1024 [ekranY] 768
   [nazwa pliku] data/plik.png
   C lub L 
   [xscreen] [yscreen] [scaleX] [scaleY] [rotacja] [alfa]
   [xscreenI] [yscreenI] [scaleXi] [scaleYi] [rotacjaI] [alfaI]
   </SPRITE>

   [nazwa obiektu] - nazwa wg kt�rej szukamy w skrypcie, istnieje wiele wpis�w dla r�nych rozdzielczo�ci ale tego samego obiektu
   [ekranX] [ekranY] - wsp�rz�dne ekranu dla szukanego obiektu
   [nazwa pliku] - nazwa pliku dla tego obiektu w tej konkretnej rozdzielczo�ci
   C - centered, L - left up  , czy wsp�rz�dna rysuj�ca ma za punkt startowy bra� �rodek obiektu, czy jego lewy g�rny r�g 
   [xscreen] [yscreen] - wsp�rzedne do rysowania na ekranie
   [scaleX] [scaleY] - skala obiektu
   [rotacja] [alfa] - k�t nachylenia, kana� alfa
   
   [xscreenI] [yscreenI] [scaleXi] [scaleYi] [rotacjaI] [alfaI] - inkrementatory dla parametr�w

   @author Jaros�aw N. Ro�y�ski
*/

#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "OGL.h"
#include "Screen.h"
#include "../io/Datafile.h"

class CSprite  
{

public:
	
	CSprite(CScreen *pScreen, char cObjectName[]);		// otwiera ze skryptu na podstawie podanych paramentrow
	CSprite(char cFilename[], CScreen *pScreen);
	CSprite(char cFilename[]);
	CSprite(char cFilename[], int iX, int iY);
	CSprite(char cFilename[], int iX, int iY, float fX, float fY);
	CSprite(char cFilename[], int iX, int iY, float fX, float fY, float fRot);
	CSprite(char cFilename[], int iX, int iY, float fAlfa);
	CSprite(char cFilename[], int iX, int iY, float fX, float fY, float fAlfa, float fRot);
	CSprite(char cFilename[], float fAlfa);

	~CSprite();

	void	Render(int x, int y, float a);
	void	Render(void);			// use top left coords
	void	RenderC(void);			// use texture centre coords

	void	Update(void);			// update factors and render
	void	UpdateC(void);
	
	void	Render(unsigned long ulTimer);		// tutaj wszystkie parapetry sa aktualizowane na podstawie timera

	void	Resize(int x1, int y1, int x2, int y2);		// set size to requested

	// set & get rotation

	void	AddRotation(float fRot);
	
   inline void	   fRotation(float fRot) { _fRotation = fRot; }
   inline float	fRotation(void) { return _fRotation; }
	
	// set & get position

	void	Position(float fX, float fY);
	void	AddPosition(float fX, float fY);

   inline float	fPositionX(void) { return _fPositionX; }
   inline void	   fPositionX(float fX) { _fPositionX = fX; }
	
   void	AddPositionX(float fX);

	inline float	fPositionY(void) { return _fPositionY; }
	inline void	fPositionY(float fY) { _fPositionX = fY; }

   void	AddPositionY(float fY);

	// set & get scale 

	void	Scale(float fX, float fY);

	void	fScaleX(float fX);
   inline float	fScaleX(void) { return _fScaleX; }

	void	fScaleY(float fY);
   inline float	fScaleY(void) { return _fScaleY; }

	// set & get size, rozmiaru nie ustawiamy, poniewa� jest on przeliczany przez funkcje skaluj�ce

   inline float	fSizeX(void) { return _fSizeX; }
   inline float	fSizeY(void) { return _fSizeY; }

	// set & get alfa

   inline void	   fAlfa(float f) { _a = f; }
   inline float	fAlfa(void) { return _a; }
   
   inline void	   AddAlfa(float f);

	// center

	inline bool		isCenter(void) { return _isCenter; }
	inline void		isCenter(bool b) { _isCenter = b; }

	// modyfikatory dla rotacji

	inline float	fRotationI(void) { return _fRotationI;  }
	inline void		fRotationI(float f) { _fRotationI = f; }

	// modyfikatory dla skali

	inline float	fScaleXI(void) { return _fScaleXI; }
	inline void		fScaleXI(float f) { _fScaleXI = f; }

	inline float	fScaleYI(void) { return _fScaleYI; }
	inline void		fScaleYI(float f) { _fScaleYI = f; }

	// modyfikator dla wsp�rz�dnych

	inline float	fPositionXI(void) { return _fPositionXI; }
	inline void		fPositionXI(float f) { _fPositionXI = f; }

	inline float	fPositionYI(void) { return _fPositionYI; }
	inline void		fPositionYI(float f) { _fPositionYI = f; }

	// modyfikator dla kana�u alfa

	inline float	fAlfaI(void) { return _fAlfaI; }
	inline void		fAlfaI(float f) { _fAlfaI = f; }

	void Color(float r, float g, float b, float a);
	void Color(float r, float g, float b);

private:

	bool				_isCenter;		// false = lewy gorny rog, true = srodek tekstury

	float				_fRotation;			
	float				_fSizeX, _fSizeY;	// oryginalny rozmiar tekstury, odczytywany z pliku
	float				_fScaleX, _fScaleY;
	float				_fPositionX, _fPositionY;

	// inkrementatory dla ka�dego wywo�ania 

	float				_fRotationI;
	float				_fScaleXI, _fScaleYI;
	float				_fPositionXI, _fPositionYI;
	float				_fAlfaI;

	unsigned long		_ulRenderTime;	// czas renderowania ostatniej klatki
	unsigned long		_ulDeltaTime;	// roznica pomiedzy ostatnim renderowaniem a aktualnym timerem
	
   // dotyczy ca�ej tekstury

	float				_r, _g, _b, _a;					// kolor naszego sprite

	oglTexture			*_pSprite;

};

 