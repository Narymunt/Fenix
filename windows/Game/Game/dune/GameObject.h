/**
   GameObject.h
   Klasa, po kt�rej dziedzicz� g��wne modu�y. 

   @author Jaros�aw N. Ro�y�ski
   @version 0.1 

   @changelog
   2014-08-27:
   - poprawki przy przenoszeniu do fenix
   - isActive jako inline
   - prze�adowany konstruktor

*/

#pragma once

#include "gfx/Screen.h"

class CGameObject
{

public:

	CGameObject();												// tutaj _pScreen jest NULL
	CGameObject(CScreen *pScreen);								// tutaj zapami�tujemy wska�nik pScreen
	~CGameObject();

	inline void			isActive(bool b) { _isActive = b; }		// czy dane zosta�y wczytane ? 
	inline bool			isActive(void) { return _isActive; }	// ustawianie r�czne flagi

	void				Open(void);								// wczytaj dane 
	void				Close(void);							// zwolnij dane

	inline void			isMouseLock(bool b) { _isMouseLock = b; }
	inline bool			isMouseLock(void) { return _isMouseLock; }

protected:

	bool				_isActive;								// czy modu� jest aktywny ? 
	bool				_isMouseLock;							// czy myszka jest zablokowana po poprzednim ekranie ? 

	CScreen				*_pScreen;								// zapamietujemy w niektorych metodach

};

