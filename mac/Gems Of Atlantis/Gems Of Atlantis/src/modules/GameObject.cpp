#include "GameObject.h"

//=== onstruktor

CGameObject::CGameObject()
{
	_isActive = false;		// data not loaded
	_isMouseLock = true;
	_pScreen = NULL;
}

//=== destructor 

CGameObject::~CGameObject()
{
	_isActive = false;
	_pScreen = NULL;
}

//=== set flag

void CGameObject::isActive(bool bState)
{
	_isActive = bState;
}

//=== return flag

bool CGameObject::isActive(void)
{
	return _isActive;
}

//=== load and prepare data

void CGameObject::Open(void)	
{
	_isActive = true;
	_isMouseLock = true;
}

//=== release data

void CGameObject::Close(void)				
{
	_isActive = false;
	_isMouseLock = true;
	_pScreen = NULL;
}

/*
int CGameObject::Render(unsigned long ulTimer, CMouse *pMouse)
{
	return 0;
}
*/