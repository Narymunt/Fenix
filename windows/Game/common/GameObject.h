#pragma once
#include "../gfx/Screen.h"

class GameObject
{

public:

	GameObject();												// tutaj _pScreen jest NULL
	GameObject(Screen *screen);								// tutaj zapamiêtujemy wskaŸnik pScreen
	~GameObject();

	virtual void		open(void);								// wczytaj dane 
	virtual void		close(void);							// zwolnij dane

	bool				_isOpen;								// czy modu³ jest aktywny ? czy dane zostaly wczytane ?
	bool				_isMouseLock;							// czy myszka jest zablokowana po poprzednim ekranie ? 

	Screen				*_screen;								// zapamietujemy w niektorych metodach

};

