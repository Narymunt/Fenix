
// mouse handle class 

#pragma once

#include <Windows.h>
#include "main.h"
#include "GameObject.h"
#include "Sprite.h"

class CMouse : public CGameObject
{

public:
	CMouse();
	~CMouse();

	void Render(void);		

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

	CSprite		*_pNormalPoint;		// bitmap
	
};


