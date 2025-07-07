#include "Button.h"

#pragma warning(disable:4996)

// tworzy przycisk na podstawie wszystkich parametrow ze skryptow

CButton::CButton(CScreen *pScreen, char cName[])
{
	FILE	*plik;
	char linia[1024];
	bool isLoad = false;
	int x,y,x1,y1,x2,y2;

	plik = NULL;
	memset(linia,0,1000);	// nie zawsze ta tablica jest czyszczona

	_onStatic = new CSprite(pScreen, linia);
	_onClick = new CSprite(pScreen, linia);
	_onOver = new CSprite(pScreen, linia);

	setHotCoords(x1,y1,x2,y2);

	isLoad = true;

}

// create 3 bitmap based button

CButton::CButton(char image[], char onOver[], char onClick[])
{
	_onStatic = new CSprite(image);
	_onOver = new CSprite(onOver);
	_onClick = new CSprite(onClick);


	_lXStart = 0;
	_lYStart = 0;
	_lXEnd = 0; 
	_lYEnd = 0;

}

// create and rescale

CButton::CButton(char clicked_name[], char onButton_name[], char m_pImage_name[], int x1, int y1, int x2, int y2)
{
	_pClicked = new CSprite(clicked_name);
	_pClicked->Resize(x1, y1, x2, y2);
	
	_pOnButton = new CSprite(onButton_name);
	_pOnButton->Resize(x1, y1, x2, y2);
	
	_pImage = new CSprite(m_pImage_name);
	_pImage->Resize(x1, y1, x2, y2);

	// bez hotx i hoty

	_lXStart = x1;
	_lYStart = y1;
	_lXEnd = x2; 
	_lYEnd = y2;

}

// destructor, release graphics 

CButton::~CButton()
{
	SafeDelete(_pClicked);
	SafeDelete(_pImage);
	SafeDelete(_pOnButton);
}

// check mouse state and draw 

int CButton::Render(CMouse *pMouse)
{

	// check hot coords 

	if ((pMouse->fMouseX()>_lXStart)&&(pMouse->fMouseX()<_lXEnd)&&(pMouse->fMouseY()>_lYStart)&&(pMouse->fMouseY()<_lYEnd))
	{
		if (pMouse->isRight())
		{
			_pClicked->Render();	
			return ON_RIGHT;
		}

		if (pMouse->isLeft())
		{
			_pClicked->Render();
			return ON_LEFT;
		}
		
		if (pMouse->isCenter())
		{
			_pClicked->Render();
			return ON_CENTER;
		}

		_pOnButton->Render();
		return ON_OVER;
	}

	_pImage->Render();
	return 0;

}

// setup button position 

void CButton::setPosition(long lX, long lY)
{
	_pClicked->Position((float)lX,(float)lY);
	_pImage->Position((float)lX,(float)lY);
	_pOnButton->Position((float)lX,(float)lY);
}

// set hot coords for button

void CButton::setHotCoords(long lXStart, long lYStart, long lXEnd, long lYEnd)
{
	_lXStart = lXStart;
	_lYStart = lYStart;
	_lXEnd = lXEnd;
	_lYEnd = lYEnd;

	_pClicked->Position((float)lXStart,(float)lYStart);
	_pImage->Position((float)lXStart,(float)lYStart);
	_pOnButton->Position((float)lXStart,(float)lYStart);

}

void CButton::set(long x1, long y1, long x2, long y2)
{
	_lXStart = x1;	_lYStart = y1;
	_lXEnd = x2; _lYEnd = y2;

	_pClicked->Position((float)x1,(float)y1);
	_pImage->Position((float)x1,(float)y1);
	_pOnButton->Position((float)x1,(float)y1);

}

