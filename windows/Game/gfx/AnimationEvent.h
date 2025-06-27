// AnimationEvent to odtwarzanie animacji z lini¹ czasu ze stosu animation
// oznacza tylko jeden event, a AnimationEventManager okresla caly stos animacji i eventow na jednym zestawie klatek

#pragma once

#include <stdio.h>
#include <vector>
#include <string>
#include "../Game.h"
#include "../common/GameObject.h"
#include "Sprite.h"
#include "Screen.h"
#include "Animation.h"

class AnimationEvent : public GameObject
{
	public:
		AnimationEvent(); // pusta kolejka, bedziemy recznie dodawac klatki
		AnimationEvent(char cFile[]); 
		~AnimationEvent();

		void	add(char cFilename[]); // Dodajemy klatkê na koniec kolejki

		void	open(void); // wczytaj dane
		void	close(void); // usun dane

		void	render(unsigned long timer);
	
		unsigned long _timerStart;		
		char	_file[1024];	// do zapamietania

		Animation* _animation;

};
