#include "Button.h"

#pragma warning(disable:4996)

// tworzy przycisk na podstawie wszystkich parametrow ze skryptow

CButton::CButton(char cName[], int iOS) :
_iOS(iOS), _pClicked(0), _pOnButton(0), _pImage(0), _isPressed(false)
{
    
}

// create 3 bitmap based button

CButton::CButton(char clicked_name[], char onButton_name[], char m_pImage_name[], int iOS) :
_iOS(iOS), _pClicked(0), _pOnButton(0), _pImage(0), _isPressed(false)
{
	_pClicked = new CSprite(clicked_name, iOS);
	_pOnButton = new CSprite(onButton_name, iOS);
	_pImage = new CSprite(m_pImage_name, iOS);

	// bez hotx i hoty

	_lXStart = 0;
	_lYStart = 0;
	_lXEnd = 0; 
	_lYEnd = 0;

}

// create and rescale

CButton::CButton(char clicked_name[], char onButton_name[], char m_pImage_name[], int x1, int y1, int x2, int y2, int iOS) :
_iOS(iOS), _pClicked(0), _pOnButton(0), _pImage(0), _lXStart(x1), _lYStart(y1), _lXEnd(x2), _lYEnd(y2), _isPressed(false)
{
	_pClicked = new CSprite(clicked_name, iOS);
	_pClicked->SetPosition((float)x1,(float)y1);
    
	_pOnButton = new CSprite(onButton_name, iOS);
    _pOnButton->SetPosition((float)x1,(float)y1);
	
	_pImage = new CSprite(m_pImage_name, iOS);
	_pImage->SetPosition((float)x1,(float)y1);
}

CButton::CButton(char clicked_name[], char onButton_name[], char m_pImage_name[], int x1, int y1, int x2, int y2) :
_pClicked(0), _pOnButton(0), _pImage(0), _lXStart(x1), _lYStart(y1), _lXEnd(x2), _lYEnd(y2), _isPressed(false)
{
	_pClicked = new CSprite(clicked_name, x1, y1, x2, y2);
	_pClicked->SetPosition((float)x1,(float)y1);
    
	_pOnButton = new CSprite(onButton_name, x1, y1, x2, y2);
    _pOnButton->SetPosition((float)x1,(float)y1);
	
	_pImage = new CSprite(m_pImage_name, x1, y1, x2, y2);
	_pImage->SetPosition((float)x1,(float)y1);
}


// destructor, release graphics 

CButton::~CButton()
{
	SafeDelete(_pClicked);
	SafeDelete(_pImage);
	SafeDelete(_pOnButton);
}

// check mouse state and draw 

int CButton::Render(CTouch *pTouch)
{

	if ((pTouch->iGetX()>_lXStart) && (pTouch->iGetX()<_lXEnd) && (pTouch->iGetY()>_lYStart) && (pTouch->iGetY()<_lYEnd))
	{
        if (pTouch->isReleased() && _isPressed)
        {
            _pClicked->Render();
            return ON_LEFT;
        }
        
        if (pTouch->isPressed())
        {
            _pOnButton->Render();
            _isPressed = true;
            return ON_OVER;
        }
            
	}
    
    _isPressed = false;
	_pImage->Render();
	return 0;

}

// setup button position 

void CButton::SetPosition(long lX, long lY)
{
	_pClicked->SetPosition((float)lX,(float)lY);
	_pImage->SetPosition((float)lX,(float)lY);
	_pOnButton->SetPosition((float)lX,(float)lY);
}

// set hot coords for button

void CButton::SetHotCoords(long lXStart, long lYStart, long lXEnd, long lYEnd)
{
	_lXStart = lXStart;
	_lYStart = lYStart;
	_lXEnd = lXEnd;
	_lYEnd = lYEnd;

	_pClicked->SetPosition((float)lXStart,(float)lYStart);
	_pImage->SetPosition((float)lXStart,(float)lYStart);
	_pOnButton->SetPosition((float)lXStart,(float)lYStart);

}

//=== end ===