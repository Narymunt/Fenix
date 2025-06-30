#include "GameObject.h"

/**
   Class construktor
   bez parametrów, _pScreen NULL
*/

GameObject::GameObject():
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

GameObject::GameObject(Screen *screen):
_isOpen(false),
_isMouseLock(true),
_screen(screen)
{

}

/** 
   Class destruktor 
   destruktor nie uwalnia wskaŸnika do ekranu
*/

GameObject::~GameObject()
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

void GameObject::open(void)	
{
	_isOpen = true;
	_isMouseLock = true;
}

/**
   Zwolnij wszystkie dane u¿ywane do renderowania modu³u.
   @param none
   @return none
*/

void GameObject::close(void)				
{
	_isOpen = false;
	_isMouseLock = true;
	_screen = NULL;
}

