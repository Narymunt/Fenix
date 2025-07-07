/**
   GameObject.cpp
   Klasa pomocnicza, po której dziedzicz¹ modu³y.

   @author Jaros³aw N. Ro¿yñski
   @version 2014-08-27
   
*/
#include "GameObject.h"

/**
   Class construktor
   bez parametrów, _pScreen NULL
*/

CGameObject::CGameObject():
_isActive(false),
_isMouseLock(true),
_pScreen(NULL)
{
}

/**
   Class construktor
   zapamiêtujemy _pScreen
   @param pScreen wskaŸnik do ekranu do zapamiêtania
*/

CGameObject::CGameObject(CScreen *pScreen):
_isActive(false),
_isMouseLock(true),
_pScreen(pScreen)
{

}

/** 
   Class destruktor 
   destruktor nie uwalnia wskaŸnika do ekranu
*/

CGameObject::~CGameObject()
{
	_isActive = false;
	_isMouseLock = true;
	_pScreen = NULL;
}

/**
   Wczytaj i zainicjalizuj dane potrzebne do renderowania modu³u.
   @param none
   @return none
*/

void CGameObject::Open(void)	
{
	_isActive = true;
	_isMouseLock = true;
}

/**
   Zwolnij wszystkie dane u¿ywane do renderowania modu³u.
   @param none
   @return none
*/

void CGameObject::Close(void)				
{
	_isActive = false;
	_isMouseLock = true;
	_pScreen = NULL;
}

