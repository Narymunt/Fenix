#include "GameObject.h"

/**
   Class construktor
   bez parametr�w, _pScreen NULL
*/

GameObject::GameObject():
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

GameObject::GameObject(Screen *screen):
_isOpen(false),
_isMouseLock(true),
_screen(screen)
{

}

/** 
   Class destruktor 
   destruktor nie uwalnia wska�nika do ekranu
*/

GameObject::~GameObject()
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

void GameObject::open(void)	
{
	_isOpen = true;
	_isMouseLock = true;
}

/**
   Zwolnij wszystkie dane u�ywane do renderowania modu�u.
   @param none
   @return none
*/

void GameObject::close(void)				
{
	_isOpen = false;
	_isMouseLock = true;
	_screen = NULL;
}

