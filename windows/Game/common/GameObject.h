#pragma once
#include "../gfx/Screen.h"

class CGameObject
{

public:

	CGameObject();												// tutaj _pScreen jest NULL
	CGameObject(CScreen *screen);								// tutaj zapamiêtujemy wskaŸnik pScreen
	~CGameObject();

	virtual void		open(void);								// wczytaj dane 
	virtual void		close(void);							// zwolnij dane

	bool				_isOpen;								// czy modu³ jest aktywny ? czy dane zostaly wczytane ?
	bool				_isMouseLock;							// czy myszka jest zablokowana po poprzednim ekranie ? 

	CScreen				*_screen;								// zapamietujemy w niektorych metodach

};

