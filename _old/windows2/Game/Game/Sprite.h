// sprite is single frame graphics object that can move, rotate, scale
// struktura dla sprite : 
// <SPRITE>
// nazwa_obiektu 
// [ekranX] 1024 [ekranY] 768
// [nazwa pliku] data/plik.png
// C lub L 
// [xscreen] [yscreen] [scaleX] [scaleY] [rotacja] [alfa]
// [xscreenI] [yscreenI] [scaleXi] [scaleYi] [rotacjaI] [alfaI]
// </SPRITE>

#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "OGL.h"
#include "Screen.h"

class CSprite  
{

public:
	
	CSprite(CScreen *pScreen, char cObjectName[]);		// otwiera ze skryptu na podstawie podanych paramentrow
	CSprite(char cFilename[]);
	CSprite(char cFilename[], int iX, int iY);
	CSprite(char cFilename[], int iX, int iY, float fX, float fY);
	CSprite(char cFilename[], int iX, int iY, float fX, float fY, float fRot);
	CSprite(char cFilename[], int iX, int iY, float fAlfa);
	CSprite(char cFilename[], int iX, int iY, float fX, float fY, float fAlfa, float fRot);
	CSprite(char cFilename[], float fAlfa);

	~CSprite();

	void	Render(void);			// use top left coords
	void	RenderC(void);			// use texture centre coords

	void	Update(void);			// update factors and render
	void	UpdateC(void);
	
	void	Render(unsigned long ulTimer);		// tutaj wszystkie parapetry sa aktualizowane na podstawie timera

	void	Resize(int x1, int y1, int x2, int y2);		// set size to requested

	inline void Resize(float x1, float y1, float x2, float y2) 
		{ Resize((int)x1,(int)y1,(int)x2,(int)y2); }

	// set & get rotation

	void	AddRotation(float fRot);
	void	fRotation(float fRot);
	float	fRotation(void);
	
	// set & get position

	void	Position(float fX, float fY);
	void	AddPosition(float fX, float fY);

	float	fPositionX(void);
	void	fPositionX(float fX);
	void	AddPositionX(float fX);

	float	fPositionY(void);
	void	fPositionY(float fY);
	void	AddPositionY(float fY);

	// set & get scale 

	void	Scale(float fX, float fY);

	void	fScaleX(float fX);
	float	fScaleX(void);

	void	fScaleY(float fY);
	float	fScaleY(void);

	// set & get size

	float	fSizeX(void);
	float	fSizeY(void);

	// set & get alfa

	void	fAlfa(float f);
	float	fAlfa(void);
	void	AddAlfa(float f);

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

	// modyfikator dla wspó³rzêdnych

	inline float	fPositionXI(void) { return _fPositionXI; }
	inline void		fPositionXI(float f) { _fPositionXI = f; }

	inline float	fPositionYI(void) { return _fPositionYI; }
	inline void		fPositionYI(float f) { _fPositionYI = f; }

	// modyfikator dla kana³u alfa

	inline float	fAlfaI(void) { return _fAlfaI; }
	inline void		fAlfaI(float f) { _fAlfaI = f; }

private:

	bool				_isCenter;		// false = lewy gorny rog, true = srodek tekstury

	float				_fRotation;			
	float				_fSizeX, _fSizeY;	// oryginalny rozmiar tekstury, odczytywany z pliku
	float				_fScaleX, _fScaleY;
	float				_fPositionX, _fPositionY;
	float				_fAlfa;

	// incrementators, how much do we want to add per rendered frame

	float				_fRotationI;
	float				_fScaleXI, _fScaleYI;
	float				_fPositionXI, _fPositionYI;
	float				_fAlfaI;

	unsigned long		_ulRenderTime;	// czas renderowania ostatniej klatki
	unsigned long		_ulDeltaTime;	// roznica pomiedzy ostatnim renderowaniem a aktualnym timerem
	// our texture

	oglTexture			*_pSprite;

};

 