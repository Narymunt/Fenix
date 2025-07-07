// game object - general object class

#pragma once

//#include "main.h"

class CGameObject
{

public:

	CGameObject();
	~CGameObject();

	void	isActive(bool bState);		// are data loaded ? 
	bool	isActive(void);				// return flag

	void	Open(void);			// load 
	void	Close(void);		// unload

//	int		Render(unsigned long ulTimer,CMouse *pMouse);		// rysuje pojedyncza klatke

protected:

	bool	_isActive;			// data loaded or not ? 

};

