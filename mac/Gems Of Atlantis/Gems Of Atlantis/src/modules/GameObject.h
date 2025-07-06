// game object - general object class

#pragma once

#include "Screen.h"

class CGameObject
{

public:

	CGameObject();
	~CGameObject();

	void				isActive(bool bState);		// are data loaded ? 
	bool				isActive(void);				// return flag

	void				Open(void);			// load 
	void				Close(void);		// unload

	inline void			isMouseLock(bool b) { _isMouseLock = b; }
	inline bool			isMouseLock(void) { return _isMouseLock; }

//	int		Render(unsigned long ulTimer,CMouse *pMouse);		// rysuje pojedyncza klatke

protected:

	bool				_isActive;			// data loaded or not ? 
	bool				_isMouseLock;		// czy myszka jest zablokowana po poprzednim ekranie ? 

	CScreen				*_pScreen;			// zapamietujemy w niektorych metodach

};

