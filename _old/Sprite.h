// sprite is single frame graphics object that can move, rotate, scale

#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "OGL.h"

class CSprite  
{

public:
	
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

private:

	float				_fRotation;			
	float				_fSizeX, _fSizeY;
	float				_fScaleX, _fScaleY;
	float				_fPositionX, _fPositionY;
	float				_fAlfa;

	// incrementators, how much do we want to add per rendered frame

	float				_fRotationI;
	float				_fSizeXI, _fSizeYI;
	float				_fScaleXI, _fScaleYI;
	float				_fPositionXI, _fPositionYI;
	float				_fAlfaI;

	// our texture

	oglTexture			*_pSprite;

};

 