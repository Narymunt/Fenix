#include "SpriteObject.h"

#pragma warning(disable : 4996)

/**
   Konstruktor klasy.
   Zapami�tuje informacje o obiekcie.

   @param cObjectname nazwa obiektu
   @param iX rozmiar ekranu dla kt�rego istnieje dany obiekt
   @param iY rozmiar ekranu dla kt�rego istnieje dany obiekt
   @param cFilename nazwa pliku dla istniej�cego obiektu
*/

CSpriteObject::CSpriteObject(char cObjectName[], int iX, int iY, char cFilename[]):
_iScreenX(iX), _iScreenY(iY)
{
	memset(_cObjectName,0,255);	// nie zawsze ta tablica jest czyszczona
	memset(_cFilename,0,255);

	strcpy(_cObjectName, cObjectName);
	strcpy(_cFilename, cFilename);
}

/**
   Destruktor klasy.

*/

CSpriteObject::~CSpriteObject()
{
	memset(_cObjectName,0,255);	// nie zawsze ta tablica jest czyszczona
	memset(_cFilename,0,255);	
}

/**
   Ustawia wsp�rz�dne obiektu na ekranie.
   
   @param fX wsp�rz�dna X
   @param fY wsp�rz�dna Y
*/

void CSpriteObject::Position(float fX, float fY)
{
	_fPositionX = fX;
	_fPositionY = fY;
}

/**
   Ustawia nowy rozmiar obiektu.
   
   @param fX skala X
   @param fY skala Y
*/

void CSpriteObject::Scale(float fX, float fY)
{
	_fScaleX = fX;
	_fScaleY = fY;
}

/**
   Sprawdza czy podana nazwa zgadza si� z t� zapami�tan�.
   
   @param cName nazwa do por�wnania
   @param true je�eli nazwa jest poprawna, false je�eli nie
*/

bool CSpriteObject::isName(char cName[])
{
	return !strcmp(cName,_cObjectName);
}
	
/**
   Ustawia inkrementatory wsp�rz�dnych.
   
   @param x inkrementator x dla ka�dej klatki
   @param y inkrementator y dla ka�dej klatki
*/

void CSpriteObject::PositionI(float x, float y)
{ 
	_fPositionXI = x; 
	_fPositionYI = y; 
}

/**
   Ustawia inkrementatory skali. 
   
   @param X inkrementator skali X
   @param Y inkrementator skali Y 
*/

void CSpriteObject::ScaleI(float x, float y)
{
	_fScaleXI = x;
	_fScaleYI = y;
}

