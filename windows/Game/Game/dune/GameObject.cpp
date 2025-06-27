/**
   GameObject.cpp
   Klasa pomocnicza, po kt�rej dziedzicz� modu�y.

   @author Jaros�aw N. Ro�y�ski
   @version 2014-08-27
   
*/
#include "GameObject.h"

/**
   Class construktor
   bez parametr�w, _pScreen NULL
*/

CGameObject::CGameObject():
_isActive(false),
_isMouseLock(true),
_pScreen(NULL)
{
}

/**
   Class construktor
   zapami�tujemy _pScreen
   @param pScreen wska�nik do ekranu do zapami�tania
*/

CGameObject::CGameObject(CScreen *pScreen):
_isActive(false),
_isMouseLock(true),
_pScreen(pScreen)
{

}

/** 
   Class destruktor 
   destruktor nie uwalnia wska�nika do ekranu
*/

CGameObject::~CGameObject()
{
	_isActive = false;
	_isMouseLock = true;
	_pScreen = NULL;
}

/**
   Wczytaj i zainicjalizuj dane potrzebne do renderowania modu�u.
   @param none
   @return none
*/

void CGameObject::Open(void)	
{
	_isActive = true;
	_isMouseLock = true;
}

/**
   Zwolnij wszystkie dane u�ywane do renderowania modu�u.
   @param none
   @return none
*/

void CGameObject::Close(void)				
{
	_isActive = false;
	_isMouseLock = true;
	_pScreen = NULL;
}

