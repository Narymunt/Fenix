// checkbox - kontrolka do zaznaczania/odznaczania

#pragma once

#include <stdio.h>
#include <string.h>
#include "../../Game.h"
#include "../gfx/Sprite.h"
#include "../ui/Mouse.h"
#include "../gfx/Screen.h"

class CCheckbox
{

	public:

		CCheckbox(CScreen *pScreen, char cScript[]);	// najwygodniejsza metoda 

		CCheckbox(CScreen *pScreen, bool isSet);
		
		CCheckbox(CScreen *pScreen, bool isSet, int iX, int iY, char cFilenameON[], char cFilenameOFF[]);
		CCheckbox(CScreen *pScreen, bool isSet, int iX, int iY, int iX1, int iY1, int iX2, int iY2, char cFilenameON[], char cFilenameOFF[]);
		
		CCheckbox(CScreen *pScreen, bool isSet, int iX, int iY, char cFilenameON[], char cFilenameOnOver[], char cFilenameOFF[], char cFilenameOffOver[]);
		CCheckbox(CScreen *pScreen, bool isSet, int iX, int iY, int iX1, int iY1, int iX2, int iY2, char cFilenameON[], char cFilenameOnOver[], char cFilenameOFF[], char cFilenameOffOver[]);
		
		~CCheckbox();

		int		Render(unsigned long ulTimer,CMouse *pMouse);	// 0 - mysz poza, 1 - clicked, 2 on over
		int		Render(int iX, int iY, unsigned long ulTimer,CMouse *pMouse);
		
      inline bool	isSet(void) {return m_isSet;}
      inline void	isSet(bool bState) { m_isSet = bState; }

		void	set(bool bState, int iX, int iY);
		void	set(bool bState, int iX, int iY, int iX1, int iY1, int iX2, int iY2);
		
		void	setHotCoords(int iX1, int iY1, int iX2, int iY2);
		void	setPosition(int iX, int iY);		
		
	private:

		bool	   m_isSet;
		
		bool  	m_isOnOverON, m_isOnOverOFF;	// czy istnieja stany podswietlenia dla wlaczonych/wylaczonych
		
		int		m_iX, m_iY;
		int		m_iX1, m_iY1, m_iX2, m_iY2;

		CSprite	*m_pImageON, *m_pImageOFF, *m_pImageONOver, *m_pImageOFFOver;

		bool	m_bMouseLock;					// nie przenos klikniecia pomiedzy ekranami
						
};

