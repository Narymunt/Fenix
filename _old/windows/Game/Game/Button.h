// 3 state button class 

#pragma once

#include <windows.h>
#include "Game.h"
#include "Sprite.h"
#include "Mouse.h"
#include "Screen.h"

#define ON_NONE		0
#define	ON_LEFT		10
#define ON_RIGHT	20
#define	ON_CENTER	30
#define ON_OVER		40

class CButton  
{
public:
	
	CButton(CScreen *pScreen, char cName[]); 
	CButton(char clicked_name[], char onDataButton_name[], char pimage_name[]);
	CButton(char clicked_name[], char onDataButton_name[], char pimage_name[], int x1, int y1, int x2, int y2);
	~CButton();

	int Render(CMouse *pMouse); // render button 

	void SetPosition(long lX, long lY);

	// hot coords
	
	void SetHotCoords(long lXStart, long lYStart, long lXEnd, long lYEnd);

private:
	
	long		_lXStart;
	long		_lYStart;
	long		_lXEnd;
	long		_lYEnd;

	CSprite		*_pClicked;		
	CSprite		*_pOnButton;	
	CSprite		*_pImage;		

};

