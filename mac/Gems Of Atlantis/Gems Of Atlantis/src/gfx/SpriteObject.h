// sprite object trzymamy po to aby przyspieszyc wczytywanie pliku

#pragma once
#include <SDL/SDL.h>
#include <SDL2_image/SDL_image.h>
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

	void	fRotation(float fRot);
	float	fRotation(void);
	
	// set & get position

	void	Position(float fX, float fY);

	float	fPositionX(void);
	void	fPositionX(float fX);

	float	fPositionY(void);
	void	fPositionY(float fY);

	// set & get scale 

	void	Scale(float fX, float fY);

	void	fScaleX(float fX);
	float	fScaleX(void);

	void	fScaleY(float fY);
	float	fScaleY(void);

	// set & get alfa

	void	fAlfa(float f);
	float	fAlfa(void);

	// center

	inline bool		isCenter(void) { return _isCenter; }
	inline void		isCenter(bool b) { _isCenter = b; }

	// modyfikatory dla rotacji

	inline float	fRotationI(void) { return _fRotationI;  }
	inline void		fRotationI(float f) { _fRotationI = f; }

	// modyfikatory dla skali

	void			ScaleI(float x, float y);

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

	int					_iScreenX, _iScreenY;

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

 