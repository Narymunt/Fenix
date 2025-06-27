// match3 module 

// isGameOver - czy wyswietlamy plansze game over zatrzymujac cala gre
// isActive - czy dane s¹ wczytane, regulujemy przez Open/Close
// isFinished - czy gra jest zakoñczona i mo¿na przejœæ do innego stanu gry, ten stan gry mo¿e byæ te¿ wywo³any np. przez escape

#pragma once

#include <SDL_mixer.h>
#include "../gfx/Animation.h"
#include "../Game.h"
#include "../common/GameObject.h"
#include "../ui/Mouse.h"
#include "../gfx/Particle2DManager.h"
#include "../ui/Button.h"
#include "../gfx/Popup.h"
#include "../io/Profile.h"
#include "../gfx/Screen.h"
#include "../gfx/FXManager.h"

class Ingame : public GameObject
{
public:
	Ingame();
	~Ingame();

	void	open(Screen *screen); // load data 
	void	close(void); // unload data 

	void	render(unsigned long timer, Mouse *mouse); // render frame

	Sprite* _black; // czarne tlo
	Sprite	*_background; // tlo

	unsigned long _timerStart; // poczatek
	unsigned long _timerPrev; // poprzedni czas wyrenderowania klatki

};

