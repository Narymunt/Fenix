
// mouse handle class 

#pragma once

#include <Windows.h>
#include "../../Game.h"
#include "../GameObject.h"
#include "../gfx/Sprite.h"

#define MOUSE_NONE		0
#define MOUSE_ARROW		10
#define MOUSE_HAND		20
#define MOUSE_WAIT		30

class CMouse : public CGameObject
{

public:
	CMouse(bool isVisible);      
	~CMouse();

	void Render(void);		
	void Render(int iState);

	inline int	iState(void) { return _iState; }
	inline void iState(int iState) { _iState = iState; }

	void isLeft(bool b);
	void isRight(bool b);
	void isCenter(bool b);

	bool isLeft(void);
	bool isRight(void);
	bool isCenter(void);

	void fMouseX(float fPosition);
	void fMouseY(float fPosition);

	float fMouseX(void);	
	float fMouseY(void);

	void fMouseXClick(float fPosition);
	void fMouseYClick(float fPosition);

	float fMouseXClick(void);
	float fMouseYClick(void);

	//=== delta dla wspolrzednych

	float fClickDeltaX(void);
	float fClickDeltaY(void);

	//=== ostatnie wspolrzedne 

	void fLastMouseX(float fPosition);
	void fLastMouseY(float fPosition);

	float fLastMouseX(void);
	float fLastMouseY(void);

   // czy kursor jest widoczny

   inline void isVisible(bool b) { _isVisible = b; }
   inline bool isVisible(void) const { return _isVisible; }

private:

	int	_iState;

	bool	_isLeft;		// left mouse button 
	bool	_isRight;		
	bool	_isCenter;	

   bool  _isVisible;

	float	_fMouseX;		// cursor positions 
	float	_fMouseY;		

	float	_fLastMouseX;
	float	_fLastMouseY;

	float	_fMouseXClick;
	float	_fMouseYClick;

	float	_fDeltaX;		// roznica pomiedzy kliknieciem a aktualnymi wspolrzednymi
	float	_fDeltaY;

	char	_cHotX;		// hot coords 
	char	_cHotY;		

	CSprite		*_pCursorArrow;		// bitmap
	CSprite		*_pCursorHand;
	CSprite		*_pCursorWait;
};


