#include "Checkbox.h"

CCheckbox::CCheckbox(char onStatic[], char onOver[], char offStatic[], char offOver[]) : _isMouseLock(true)
{init(NULL, onStatic, onOver, offStatic, offOver, 0, 0, 0, 0, 0, 0, false);}

CCheckbox::CCheckbox(char onStatic[], char onOver[], char offStatic[], char offOver[], bool b) : _isMouseLock(true)
{init(NULL, onStatic, onOver, offStatic, offOver, 0, 0, 0, 0, 0, 0, b);}

CCheckbox::CCheckbox(char onStatic[], char onOver[], char offStatic[], char offOver[], int x, int y) : _isMouseLock(true)
{init(NULL, onStatic, onOver, offStatic, offOver, x, y, 0, 0, 0, 0, false);}

CCheckbox::CCheckbox(char onStatic[], char onOver[], char offStatic[], char offOver[], int x, int y, bool b) : _isMouseLock(true)
{init(NULL, onStatic, onOver, offStatic, offOver, x, y, 0, 0, 0, 0, b);}

CCheckbox::CCheckbox(char onStatic[], char onOver[], char offStatic[], char offOver[], int x1, int y1, int x2, int y2) : _isMouseLock(true)
{init(NULL, onStatic, onOver, offStatic, offOver, x1, y1, x1, y1, x2, y2, false);}

CCheckbox::CCheckbox(char onStatic[], char onOver[], char offStatic[], char offOver[], int x1, int y1, int x2, int y2, bool b) : _isMouseLock(true)
{init(NULL, onStatic, onOver, offStatic, offOver, x1, y1, x1, y1, x2, y2, b);}

CCheckbox::CCheckbox(char onStatic[], char onOver[], char offStatic[], char offOver[], int x, int y, int x1, int y1, int x2, int y2) : _isMouseLock(true)
{init(NULL, onStatic, onOver, offStatic, offOver, x, y, x1, y1, x2, y2, false);}

CCheckbox::CCheckbox(char onStatic[], char onOver[], char offStatic[], char offOver[], int x, int y, int x1, int y1, int x2, int y2, bool b) : _isMouseLock(true)
{init(NULL, onStatic, onOver, offStatic, offOver, x, y, x1, y1, x2, y2, b);}

CCheckbox::CCheckbox(CScreen *screen, char onStatic[], char onOver[], char offStatic[], char offOver[]) : _isMouseLock(true)
{init(screen, onStatic, onOver, offStatic, offOver, 0, 0, 0, 0, 0, 0, false);}

CCheckbox::CCheckbox(CScreen *screen, char onStatic[], char onOver[], char offStatic[], char offOver[], bool b) : _isMouseLock(true)
{init(screen, onStatic, onOver, offStatic, offOver, 0, 0, 0, 0, 0, 0, b);}

CCheckbox::CCheckbox(CScreen *screen, char onStatic[], char onOver[], char offStatic[], char offOver[], int x, int y) : _isMouseLock(true)
{init(screen, onStatic, onOver, offStatic, offOver, x, y, 0, 0, 0, 0, false);}

CCheckbox::CCheckbox(CScreen *screen, char onStatic[], char onOver[], char offStatic[], char offOver[], int x, int y, bool b) : _isMouseLock(true)
{init(screen, onStatic, onOver, offStatic, offOver, x, y, 0, 0, 0, 0, b);}

CCheckbox::CCheckbox(CScreen *screen, char onStatic[], char onOver[], char offStatic[], char offOver[], int x1, int y1, int x2, int y2) : _isMouseLock(true)
{init(screen, onStatic, onOver, offStatic, offOver, x1, y1, x1, y1, x2, y2, false);}

CCheckbox::CCheckbox(CScreen *screen, char onStatic[], char onOver[], char offStatic[], char offOver[], int x1, int y1, int x2, int y2, bool b) : _isMouseLock(true)
{init(screen, onStatic, onOver, offStatic, offOver, x1, y1, x1, y1, x2, y2, b);}

CCheckbox::CCheckbox(CScreen *screen, char onStatic[], char onOver[], char offStatic[], char offOver[], int x, int y, int x1, int y1, int x2, int y2) : _isMouseLock(true)
{init(screen, onStatic, onOver, offStatic, offOver, x, y, x1, y1, x2, y2, false);}

CCheckbox::CCheckbox(CScreen *screen, char onStatic[], char onOver[], char offStatic[], char offOver[], int x, int y, int x1, int y1, int x2, int y2, bool b) : _isMouseLock(true)
{init(screen, onStatic, onOver, offStatic, offOver, x, y, x1, y1, x2, y2, b);}


void CCheckbox::init(CScreen *screen, char onStatic[], char onOver[], char offStatic[], char offOver[], int x, int y, int x1, int y1, int x2, int y2, bool b)
{
	if (screen != NULL)
	{
		_onStatic = new CSprite(onStatic);
		_onOver = new CSprite(onOver);
		_offStatic = new CSprite(offStatic);
		_offOver = new CSprite(offOver);
	}
	else
	{

	}

	if (x == y && x== 0 && x==x2)	// brak podanych x1,y1,x2,y2
	{
		_onStatic->position(x, y);
		_onOver->position(x, y);
	}
}





CCheckbox::CCheckbox(CScreen *pScreen, bool isSet, int iX, int iY, int iX1, int iY1, int iX2, int iY2, char cFilenameON[], char cFilenameOFF[])
{
	m_isSet = isSet;
	m_iX = iX; 
	m_iY = iY; 
	m_iX1 = iX1; 
	m_iY1 = iY1; 
	m_iX2 = iX2; 
	m_iY2 = iY2; 

	// zerowanie wskaznikow sprite'ow

	m_pImageON = NULL;
	m_pImageOFF = NULL;
	m_pImageONOver = NULL;
	m_pImageOFFOver = NULL;

	m_pImageON = new CSprite(pScreen, cFilenameON);
	m_pImageOFF = new CSprite(pScreen, cFilenameOFF);

	m_bMouseLock = true;

}

CCheckbox::CCheckbox(CScreen *pScreen, bool isSet, int iX, int iY, char cFilenameON[], char cFilenameOnOver[], char cFilenameOFF[], char cFilenameOffOver[])
{
	m_isSet = isSet;
	m_iX = iX; 
	m_iY = iY; 

	// zerowanie wskaznikow sprite'ow

	m_pImageON = NULL;
	m_pImageOFF = NULL;
	m_pImageONOver = NULL;
	m_pImageOFFOver = NULL;

	m_pImageON = new CSprite(pScreen, cFilenameON);
	m_pImageOFF = new CSprite(pScreen, cFilenameOFF);

	m_pImageONOver = new CSprite(pScreen, cFilenameOnOver);
	m_pImageOFFOver = new CSprite(pScreen, cFilenameOffOver);

	m_bMouseLock = true;

}

CCheckbox::CCheckbox(CScreen *pScreen, bool isSet, int iX, int iY, int iX1, int iY1, int iX2, int iY2, char cFilenameON[], char cFilenameOnOver[], char cFilenameOFF[], char cFilenameOffOver[])
{
	m_isSet = isSet;
	m_iX = iX; 
	m_iY = iY; 
	m_iX1 = iX1; 
	m_iY1 = iY1; 
	m_iX2 = iX2; 
	m_iY2 = iY2; 

	// zerowanie wskaznikow sprite'ow

	m_pImageON = NULL;
	m_pImageOFF = NULL;
	m_pImageONOver = NULL;
	m_pImageOFFOver = NULL;

	m_pImageON = new CSprite(pScreen, cFilenameON);
	m_pImageOFF = new CSprite(pScreen, cFilenameOFF);

	m_pImageONOver = new CSprite(pScreen, cFilenameOnOver);
	m_pImageOFFOver = new CSprite(pScreen, cFilenameOffOver);

	m_bMouseLock = true;
}
		
CCheckbox::~CCheckbox()
{
	SafeDelete(m_pImageON);
	SafeDelete(m_pImageOFF);
	SafeDelete(m_pImageONOver);
	SafeDelete(m_pImageOFFOver);

}

int CCheckbox::Render(unsigned long ulTimer,CMouse *pMouse)	// 0 - mysz poza, 1 - clicked, 2 on over
{
	// renderuj przycisk

	if (m_pImageONOver!=NULL)	// czy kursor podswietla
	{
		if (m_isSet)
		{
			if ((pMouse->fMouseX()>m_iX1)&&(pMouse->fMouseX()<m_iX2)&&(pMouse->fMouseY()>m_iY1)&&(pMouse->fMouseY()<m_iY2))	// mysz nad obiektem - rysuj podswietlone
			{
				m_pImageONOver->Position((float)m_iX,(float)m_iY);
				m_pImageONOver->Render();
			}
			else
			{
				m_pImageON->Position((float)m_iX,(float)m_iY);	// jesli nie, rysuj normalne
				m_pImageON->Render();
			}
		}
		else
		{
			if ((pMouse->fMouseX()>m_iX1)&&(pMouse->fMouseX()<m_iX2)&&(pMouse->fMouseY()>m_iY1)&&(pMouse->fMouseY()<m_iY2))	// mysz nad obiektem - rysuj podswietlone
			{
				m_pImageOFFOver->Position((float)m_iX,(float)m_iY);
				m_pImageOFFOver->Render();
			}
			else
			{
				m_pImageOFF->Position((float)m_iX,(float)m_iY);	// jesli nie, rysuj normalne
				m_pImageOFF->Render();
			}
		}
	}
	else	// bez podswietlania
	{
		if (m_isSet)
		{
			m_pImageON->Position((float)m_iX,(float)m_iY);
			m_pImageON->Render();
		}
		else
		{
			m_pImageOFF->Position((float)m_iX,(float)m_iY);
			m_pImageOFF->Render();
		}
	}
	
	// zmiana stanu przycisku

	if (!m_bMouseLock)
	{
		if ((pMouse->fMouseX()>m_iX1)&&(pMouse->fMouseX()<m_iX2)&&(pMouse->fMouseY()>m_iY1)&&(pMouse->fMouseY()<m_iY2)&&(pMouse->isLeft()))	// mysz nad obiektem - rysuj podswietlone
		{
			if (m_isSet)
			{
				m_isSet = false;
			}
			else
			{
				m_isSet = true;
			}
		}
	}

	// zmiana stanu blokady myszy

	if (pMouse->isLeft())
	{
		m_bMouseLock = true;
	}
	else
	{
		m_bMouseLock = false;
	}

	return 0; 
}

int CCheckbox::Render(int iX, int iY, unsigned long ulTimer,CMouse *pMouse)
{
   int deltaX,deltaY;

   m_iX = iX;
   m_iY = iY;

   m_pImageON->Position((float)iX,(float)iY);
   m_pImageOFF->Position((float)iX,(float)iY);
   m_pImageONOver->Position((float)iX,(float)iY);
   m_pImageOFFOver->Position((float)iX,(float)iY);

   deltaX = m_iX2 - m_iX1;
   deltaY = m_iY2 - m_iY1;

   setHotCoords(iX,iY, iX+deltaX,iY+deltaY);

   return Render(ulTimer,pMouse); 
}	

void CCheckbox::set(bool bState, int iX, int iY)
{
	m_isSet = bState;
	m_iX = iX; 
	m_iY = iY; 
}

void CCheckbox::set(bool bState, int iX, int iY, int iX1, int iY1, int iX2, int iY2)
{
	m_isSet = bState;
	m_iX = iX; 
	m_iY = iY; 
	m_iX1 = iX1; 
	m_iY1 = iY1; 
	m_iX2 = iX2; 
	m_iY2 = iY2; 
}

void CCheckbox::setHotCoords(int iX1, int iY1, int iX2, int iY2)
{
	m_iX1 = iX1; 
	m_iY1 = iY1; 
	m_iX2 = iX2; 
	m_iY2 = iY2; 
}

void CCheckbox::setPosition(int iX, int iY)
{
	m_iX = iX; 
	m_iY = iY; 
}
