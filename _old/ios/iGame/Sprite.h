#pragma once

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#include "SDL.h"
#include "SDL_image.h"
#include "Screen.h"

class CSprite  
{

public:

	// w tym przypadku nazwa pliku jest bezwzgledna

	CSprite(char cFilename[]);
	CSprite(char cFilename[], int iX, int iY);
	CSprite(char cFilename[], int iX, int iY, float fX, float fY);
	CSprite(char cFilename[], int iX, int iY, float fX, float fY, float fRot);
	CSprite(char cFilename[], int iX, int iY, float fAlfa);
	CSprite(char cFilename[], int iX, int iY, float fX, float fY, float fAlfa, float fRot);
	CSprite(char cFilename[], float fAlfa);

	// w tych konstruktorach generujemy nazwy plikow z uwzglednieniem rozdzielczosci

	CSprite(CScreen *pScreen, char cFilename[]);
	CSprite(CScreen *pScreen, char cFilename[], int iX, int iY);
	CSprite(CScreen *pScreen, char cFilename[], int iX, int iY, float fX, float fY);
	CSprite(CScreen *pScreen, char cFilename[], int iX, int iY, float fX, float fY, float fRot);
	CSprite(CScreen *pScreen, char cFilename[], int iX, int iY, float fAlfa);
	CSprite(CScreen *pScreen, char cFilename[], int iX, int iY, float fX, float fY, float fAlfa, float fRot);
	CSprite(CScreen *pScreen, char cFilename[], float fAlfa);

	~CSprite();

	SDL_PixelFormat oglGetPixelFormat(GLenum glFormat);

	void	Init(CScreen *pScreen, char cFilename[]);

	void	Render(int x, int y, float a);
	void	Render(void);						// use top left coords
	void	RenderC(void);						// use texture centre coords

	void	Update(void);						// update factors and render
	void	UpdateC(void);
	
	void	Render(unsigned long ulTimer);		// tutaj wszystkie parapetry sa aktualizowane na podstawie timera

	void	Resize(int x1, int y1, int x2, int y2);		// set size to requested

	void	Fullscreen(CScreen *pScreen);


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

	// oryginalny rozmiar tekstur

	inline float 	fOriginalX(void) { return _fOriginalX; }
	inline void		fOriginalX(float f) { _fOriginalX = f; }

	inline float	fOriginalY(void) { return _fOriginalY; }
	inline void		fOriginalY(float f) { _fOriginalY = f; }

    float				_fPositionX, _fPositionY;    
    float				_fAlfa;
    
private:

	bool				_isCenter;					// false = lewy gorny rog, true = srodek tekstury

	float				_fRotation;			
	float				_fSizeX, _fSizeY;			// aktualny rozmiar tekstury liczony w pixelach
	float				_fOriginalX, _fOriginalY;	// pierwotny rozmiar textury
	float				_fScaleX, _fScaleY;

	// incrementators, how much do we want to add per rendered frame

	float				_fRotationI;
	float				_fScaleXI, _fScaleYI;
	float				_fPositionXI, _fPositionYI;
	float				_fAlfaI;

	unsigned long		_ulRenderTime;	// czas renderowania ostatniej klatki
	unsigned long		_ulDeltaTime;	// roznica pomiedzy ostatnim renderowaniem a aktualnym timerem
	// our texture

	GLuint				_pSprite;		// identyfikator tekstury

};

 

