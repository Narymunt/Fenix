// checkbox - kontrolka do zaznaczania/odznaczania

#pragma once

#include <stdio.h>
#include <string.h>
#include "Game.h"
#include "Sprite.h"
#include "Mouse.h"

class CCheckbox
{

	public:

		CCheckbox(char cScript[]);	// najwygodniejsza metoda 

		CCheckbox(bool isSet);
		
		CCheckbox(bool isSet, int iX, int iY, char cFilenameON[], char cFilenameOFF[]);
		CCheckbox(bool isSet, int iX, int iY, int iX1, int iY1, int iX2, int iY2, char cFilenameON[], char cFilenameOFF[]);
		
		CCheckbox(bool isSet, int iX, int iY, char cFilenameON[], char cFilenameOnOver[], char cFilenameOFF[], char cFilenameOffOver[]);
		CCheckbox(bool isSet, int iX, int iY, int iX1, int iY1, int iX2, int iY2, char cFilenameON[], char cFilenameOnOver[], char cFilenameOFF[], char cFilenameOffOver[]);
		
		~CCheckbox();

		int		Render(unsigned long ulTimer,CMouse *pMouse);	// 0 - mysz poza, 1 - clicked, 2 on over
		int		Render(int iX, int iY, unsigned long ulTimer,CMouse *pMouse);
		
		bool	isSet(void);

		void	Set(bool bState);
		void	Set(bool bState, int iX, int iY);
		void	Set(bool bState, int iX, int iY, int iX1, int iY1, int iX2, int iY2);
		
		void	SetHotCoords(int iX1, int iY1, int iX2, int iY2);
		void	SetPosition(int iX, int iY);
		
		
	private:

		bool	m_isSet;
		
		bool 	m_isOnOverON, m_isOnOverOFF;	// czy istnieja stany podswietlenia dla wlaczonych/wylaczonych
		
		int		m_iX, m_iY;
		int		m_iX1, m_iY1, m_iX2, m_iY2;

		CSprite	*m_pImageON, *m_pImageOFF, *m_pImageONOver, *m_pImageOFFOver;

		bool	m_bMouseLock;					// nie przenos klikniecia pomiedzy ekranami
						
};

