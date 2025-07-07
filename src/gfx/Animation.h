/**
   Animation.h
   Animacja to stos klatek animacji, nie powtarzaj¹cych siê.
   Dopiero event okreœla, które klatki z animacji nale¿y odtwarzaæ i w jakiej kolejnoœci

   @author Jaros³aw N. Ro¿yñski

*/

#pragma once

#include <stdio.h>
#include <vector>
#include <string>
#include "../Game.h"
#include "../common/GameObject.h"
#include "Sprite.h"
#include "Screen.h"

class CAnimation : public CGameObject
{
	public:
		CAnimation(char cFile[]);									         // plik .ini z opisami
		CAnimation(char cFile[], int iFrameCount, char cExt[]);		// dodaje animacje plikXXX.ext, klatki liczone sa od 0
		CAnimation(CScreen *pScreen, char cObjectName[]);			   // dodaje animacje i wczytuje dane, calosc ze skryptu
		~CAnimation();
	
      inline void	iFrameCount(int i) { _iFrameCount = i; }
      inline int	iFrameCount(void) { return _iFrameCount; }	

		void	Add(char cFilename[]);

		void	Open(CScreen *pScreen);	                              // wczytaj dane
		void	Close(void);						                        // usun dane

		void	Render(int iFrame);
		void	Render(int iFrame, int iX, int iY);
		void	Render(int iFrame, int iX, int iY, unsigned char alfa);	
		void	Render(int iFrame, int iX, int iY, float fScaleX, float fScaleY);
		void	Render(int iFrame, int iX, int iY, float fScaleX, float fScaleY, float fRotation);
		void	Render(int iFrame, int iX, int iY, float fScaleX, float fScaleY, float fRotation, float fRotationX, float fRotationY);
		
	private:
		
		char	_cFile[200];
		int	_iFrameCount;
		char	_cExt[3];

		std::vector <CSprite*>	m_pSprite;		                     // tutaj nasze bitmapy
};