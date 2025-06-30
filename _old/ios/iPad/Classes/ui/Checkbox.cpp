#include "Checkbox.h"

CCheckbox::CCheckbox(bool isSet, int iX, int iY, int iX1, int iY1, int iX2, int iY2, char cFilenameON[], char cFilenameOnOver[], char cFilenameOFF[], char cFilenameOffOver[])
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

	m_pImageON = new CSprite(cFilenameON);
	m_pImageOFF = new CSprite(cFilenameOFF);

	m_pImageONOver = new CSprite(cFilenameOnOver);
	m_pImageOFFOver = new CSprite(cFilenameOffOver);

	m_bMouseLock = true;
}
		
CCheckbox::~CCheckbox()
{
	SafeDelete(m_pImageON);
	SafeDelete(m_pImageOFF);
	SafeDelete(m_pImageONOver);
	SafeDelete(m_pImageOFFOver);

}

int CCheckbox::Render(unsigned long ulTimer,CTouch *pTouch)	// 0 - mysz poza, 1 - clicked, 2 on over
{
	// renderuj przycisk

	if (m_pImageONOver!=NULL)	// czy kursor podswietla
	{
		if (m_isSet)
		{
			if ((pTouch->iGetX()>m_iX1)&&(pTouch->iGetX()<m_iX2)&&(pTouch->iGetY()>m_iY1)&&(pTouch->iGetY()<m_iY2))	// mysz nad obiektem - rysuj podswietlone
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
			if ((pTouch->iGetX()>m_iX1)&&(pTouch->iGetX()<m_iX2)&&(pTouch->iGetY()>m_iY1)&&(pTouch->iGetY()<m_iY2))	// mysz nad obiektem - rysuj podswietlone
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
		if ((pTouch->iGetX()>m_iX1)&&(pTouch->iGetX()<m_iX2)&&(pTouch->iGetY()>m_iY1)&&(pTouch->iGetY()<m_iY2)&&(pTouch->isPressed()))	// mysz nad obiektem - rysuj podswietlone
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

	if (pTouch->isPressed())
	{
		m_bMouseLock = true;
	}
	else
	{
		m_bMouseLock = false;
	}

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
