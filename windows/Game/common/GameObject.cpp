#include "GameObject.h"

/**
   Class construktor
   bez parametr�w, _pScreen NULL
*/

CGameObject::CGameObject():
_isOpen(false),
_isMouseLock(true),
_screen(NULL)
{
}

/**
   Class construktor
   zapami�tujemy _pScreen
   @param pScreen wska�nik do ekranu do zapami�tania
*/

CGameObject::CGameObject(CScreen *pScreen):
_isOpen(false),
_isMouseLock(true),
_screen(pScreen)
{

}

/** 
   Class destruktor 
   destruktor nie uwalnia wska�nika do ekranu
*/

CGameObject::~CGameObject()
{
	_isOpen = false;
	_isMouseLock = true;
	_screen = NULL;
}

/**
   Wczytaj i zainicjalizuj dane potrzebne do renderowania modu�u.
   @param none
   @return none
*/

void CGameObject::open(void)	
{
	_isOpen = true;
	_isMouseLock = true;
}

/**
   Zwolnij wszystkie dane u�ywane do renderowania modu�u.
   @param none
   @return none
*/

void CGameObject::close(void)				
{
	_isOpen = false;
	_isMouseLock = true;
	_screen = NULL;
}

