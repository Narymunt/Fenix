// Animacja to stos klatek animacji, nie powtarzaj¹cych siê.
// Dopiero event okreœla, które klatki z animacji nale¿y odtwarzaæ i w jakiej kolejnoœci

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
		CAnimation(); // pusta kolejka, bedziemy recznie dodawac klatki
		CAnimation(char cFile[], int iFrameCount, char cExt[]); // dodaje animacje plikXXX.ext, klatki liczone sa od 0, NIE WCZYTUJE
		~CAnimation();

		void	add(char cFilename[]); // Dodajemy klatkê na koniec kolejki

		void	open(void); // wczytaj dane
		void	close(void); // usun dane

		void	render(int iFrame);
		void	render(int iFrame, int iX, int iY);
		void	render(int iFrame, int iX, int iY, unsigned char alfa);	
		void	render(int iFrame, int iX, int iY, float fScaleX, float fScaleY);
		void	render(int iFrame, int iX, int iY, float fScaleX, float fScaleY, float fRotation);
		void	render(int iFrame, int iX, int iY, float fScaleX, float fScaleY, float fRotation, float fRotationX, float fRotationY);
	
		int		_frameCount;		
		char	_file[1024];
		char	_ext[3];

		std::vector <CSprite*>	_sprite;		                     // tutaj nasze bitmapy
};
