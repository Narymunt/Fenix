// Animacja to stos klatek animacji, nie powtarzaj¹cych siê., czyli np. klatki ruchu ludka
// AnimationEvent - ktore klatki po kolei ma odtworzyc + ma³e modyfikatory pozycji, czyli np. ludek idzie, klatki 1,2,3,4,3,2,1 itp
// AnimationTrack - dodanie modyfikatorów w postaci spline z okreœleniem predkosci odtwarzania, czyli od 0 do 1920 w petli AnimationEvent


#pragma once

#include <stdio.h>
#include <vector>
#include <string>
#include "../Game.h"
#include "../common/GameObject.h"
#include "Sprite.h"
#include "Screen.h"

class Animation : public GameObject
{
	public:
		Animation(); // pusta kolejka, bedziemy recznie dodawac klatki
		Animation(char cFile[], int iFrameCount, char cExt[]); // dodaje animacje plikXXX.ext, klatki liczone sa od 0, NIE WCZYTUJE
		~Animation();

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

		std::vector <Sprite*>	_sprite;		                     // tutaj nasze bitmapy
};
