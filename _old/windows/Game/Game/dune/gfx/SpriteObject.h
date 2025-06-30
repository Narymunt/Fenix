/**
   SpriteObject.h
   SpriteObject trzymamy po to, aby przyspieszyc wczytywanie pliku.
   Zawiera wszystkie informacje o obiekcie, ale nie posiada tekstury do renderowania.

   @author Jaros³aw Ro¿yñski   
*/

#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "OGL.h"

class CSpriteObject
{

public:

	CSpriteObject(char cObjectName[], int iX, int iY, char cFilename[]);
	~CSpriteObject();

	// do porownywania nazw

	bool	isName(char cName[]);
	inline char *cFilename() { return _cFilename; }

	// parametru ekranu dla ktorego trzymany jest ten wpis

	inline void		iScreenX(int i) { _iScreenX = i; }
	inline int		iScreenX() { return _iScreenX; }

	inline void		iScreenY(int i) { _iScreenY = i; }
	inline int		iScreenY() { return _iScreenY; }

	// set & get rotation

   inline void	   fRotation(float fRot) { _fRotation = fRot; }
   inline float	fRotation(void) { return _fRotation; }
	
	// set & get position

	void	Position(float fX, float fY);

   inline float	fPositionX(void) { return _fPositionX; }
   inline void	   fPositionX(float fX) { _fPositionX = fX; }

   inline float	fPositionY(void) { return _fPositionY; }
   inline void	   fPositionY(float fY) { _fPositionY = fY; }

	// set & get scale 

	void	Scale(float fX, float fY);

   inline void	   fScaleX(float fX) { _fScaleX = fX; }
   inline float	fScaleX(void) { return _fScaleX; }

   inline void	   fScaleY(float fY) { _fScaleY = fY; }
   inline float	fScaleY(void) { return _fScaleY; }

	// set & get alfa

   inline void	   fAlfa(float f) { _fAlfa = f; }
   inline float	fAlfa(void) { return _fAlfa; }

	// center

	inline bool		isCenter(void) { return _isCenter; }
	inline void		isCenter(bool b) { _isCenter = b; }

	// modyfikatory dla rotacji

	inline float	fRotationI(void) { return _fRotationI;  }
	inline void		fRotationI(float f) { _fRotationI = f; }

	// modyfikatory dla skali

	void			   ScaleI(float x, float y);

	inline float	fScaleXI(void) { return _fScaleXI; }
	inline void		fScaleXI(float f) { _fScaleXI = f; }

	inline float	fScaleYI(void) { return _fScaleYI; }
	inline void		fScaleYI(float f) { _fScaleYI = f; }

	// modyfikator dla wspó³rzêdnych

	void			PositionI(float x, float y);

	inline float	fPositionXI(void) { return _fPositionXI; }
	inline void		fPositionXI(float f) { _fPositionXI = f; }

	inline float	fPositionYI(void) { return _fPositionYI; }
	inline void		fPositionYI(float f) { _fPositionYI = f; }

	// modyfikator dla kana³u alfa

	inline float	fAlfaI(void) { return _fAlfaI; }
	inline void		fAlfaI(float f) { _fAlfaI = f; }

private:

	bool				_isCenter;		// false = lewy gorny rog, true = srodek tekstury

	int				_iScreenX, _iScreenY;

	float				_fRotation;			
	float				_fScaleX, _fScaleY;
	float				_fPositionX, _fPositionY;
	float				_fAlfa;

	// incrementators, how much do we want to add per rendered frame

	float				_fRotationI;
	float				_fScaleXI, _fScaleYI;
	float				_fPositionXI, _fPositionYI;
	float				_fAlfaI;

	char				_cObjectName[256];	// nazwa naszego obiektu
	char				_cFilename[256];	// nazwa pliku

};

 