// 3 state button class 

#pragma once

#include "config.h"
#include "Sprite.h"
#include "Touch.h"

#define ON_NONE		0
#define	ON_LEFT		10
#define ON_RIGHT	20
#define	ON_CENTER	30
#define ON_OVER		40

class CButton  
{
public:
	
	CButton(char cName[], int iOS);      // ze skryptu
	CButton(char clicked_name[], char onDataButton_name[], char pimage_name[], int iOS);
	CButton(char clicked_name[], char onDataButton_name[], char pimage_name[], int x1, int y1, int x2, int y2, int iOS);
    CButton(char clicked_name[], char onDataButton_name[], char pimage_name[], int x1, int y1, int x2, int y2);
	~CButton();

	int Render(CTouch *pMouse); // render button

	void SetPosition(long lX, long lY);

	// hot coords
	
	void SetHotCoords(long lXStart, long lYStart, long lXEnd, long lYEnd);

    inline int x1() { return _lXStart; }
    inline int y1() { return _lYStart; }
    inline int x2() { return _lXEnd; }
    inline int y2() { return _lYEnd; }
    
    inline int iSizeX() { return _lXEnd - _lXStart; }
    inline int iSizeY() { return _lYEnd - _lYStart; }
    
    inline bool isPressed(void) { return _isPressed; }     // do wielokrotnego używania przycisku na tym samym ekranie
    inline void isPressed(bool b) { _isPressed = b; }
    
private:
	
    int         _iSizeX, _iSizeY;
    
    int         _iOS;
    
	long		_lXStart;
	long		_lYStart;
	long		_lXEnd;
	long		_lYEnd;

	CSprite		*_pClicked;		
	CSprite		*_pOnButton;	
	CSprite		*_pImage;		

    bool        _isPressed;       // kontrolujemy stan nacisniecia, poniewaz puszczenie a nie nacisniecie decyduje
    
};

