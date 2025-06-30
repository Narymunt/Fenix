#include "GameObject.h"

/**
   Class construktor
   bez parametrów, _pScreen NULL
*/

CGameObject::CGameObject():
_isOpen(false),
_isMouseLock(true),
_screen(NULL)
{
}

/**
   Class construktor
   zapamiêtujemy _pScreen
   @param pScreen wskaŸnik do ekranu do zapamiêtania
*/

CGameObject::CGameObject(CScreen *pScreen):
_isOpen(false),
_isMouseLock(true),
_screen(pScreen)
{

}

/** 
   Class destruktor 
   destruktor nie uwalnia wskaŸnika do ekranu
*/

CGameObject::~CGameObject()
{
	_isOpen = false;
	_isMouseLock = true;
	_screen = NULL;
}

/**
   Wczytaj i zainicjalizuj dane potrzebne do renderowania modu³u.
   @param none
   @return none
*/

void CGameObject::open(void)	
{
	_isOpen = true;
	_isMouseLock = true;
}

/**
   Zwolnij wszystkie dane u¿ywane do renderowania modu³u.
   @param none
   @return none
*/

void CGameObject::close(void)				
{
	_isOpen = false;
	_isMouseLock = true;
	_screen = NULL;
}

