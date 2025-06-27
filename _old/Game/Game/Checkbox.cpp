#include "Checkbox.h"

CCheckbox::CCheckbox(CScreen *pScreen, char cScript[])	// najwygodniejsza metoda 
{

	// zerowanie wskaznikow sprite'ow

	m_pImageON = NULL;
	m_pImageOFF = NULL;
	m_pImageONOver = NULL;
	m_pImageOFFOver = NULL;

	m_bMouseLock = true;

}

CCheckbox::CCheckbox(CScreen *pScreen, bool isSet)
{
	m_isSet = isSet;
}

CCheckbox::CCheckbox(CScreen *pScreen, bool isSet, int iX, int iY, char cFilenameON[], char cFilenameOFF[])
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

	m_bMouseLock = true;

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

	return 0; 
}
		
bool CCheckbox::isSet(void)
{
	return m_isSet;
}
	
void CCheckbox::Set(bool bState)
{
	m_isSet = bState;
}

void CCheckbox::Set(bool bState, int iX, int iY)
{
	m_isSet = bState;
	m_iX = iX; 
	m_iY = iY; 
}

void CCheckbox::Set(bool bState, int iX, int iY, int iX1, int iY1, int iX2, int iY2)
{
	m_isSet = bState;
	m_iX = iX; 
	m_iY = iY; 
	m_iX1 = iX1; 
	m_iY1 = iY1; 
	m_iX2 = iX2; 
	m_iY2 = iY2; 
}

void CCheckbox::SetHotCoords(int iX1, int iY1, int iX2, int iY2)
{
	m_iX1 = iX1; 
	m_iY1 = iY1; 
	m_iX2 = iX2; 
	m_iY2 = iY2; 
}

void CCheckbox::SetPosition(int iX, int iY)
{
	m_iX = iX; 
	m_iY = iY; 
}
