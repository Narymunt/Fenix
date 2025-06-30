
// mouse handle class 

#pragma once

#include "Game.h"
#include "GameObject.h"
#include "Sprite.h"

#define MOUSE_NONE		0
#define	MOUSE_ARROW		10
#define MOUSE_HAND		20
#define MOUSE_WAIT		30

class CMouse : public CGameObject
{

public:
	CMouse();
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

	float fGetClickDeltaX(void);
	float fGetClickDeltaY(void);

	void fLastMouseX(float fPosition);
	void fLastMouseY(float fPosition);

	float fLastMouseX(void);
	float fLastMouseY(void);

private:

	int		_iState;

	bool	_isLeft;		// left mouse button 
	bool	_isRight;		
	bool	_isCenter;	
	
	float	_fMouseX;		// cursor positions 
	float	_fMouseY;		

	float	_fLastMouseX;
	float	_fLastMouseY;

	float	_fMouseXClick;
	float	_fMouseYClick;

	char	_cHotX;		// hot coords 
	char	_cHotY;		

	CSprite		*_pCursorArrow;		// bitmap
	CSprite		*_pCursorHand;
	CSprite		*_pCursorWait;
};


