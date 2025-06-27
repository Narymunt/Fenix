#include "SpriteObject.h"

#pragma warning(disable : 4996)

/**
   Konstruktor klasy.
   Zapamiêtuje informacje o obiekcie.

   @param cObjectname nazwa obiektu
   @param iX rozmiar ekranu dla którego istnieje dany obiekt
   @param iY rozmiar ekranu dla którego istnieje dany obiekt
   @param cFilename nazwa pliku dla istniej¹cego obiektu
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
   Ustawia wspó³rzêdne obiektu na ekranie.
   
   @param fX wspó³rzêdna X
   @param fY wspó³rzêdna Y
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
   Sprawdza czy podana nazwa zgadza siê z t¹ zapamiêtan¹.
   
   @param cName nazwa do porównania
   @param true je¿eli nazwa jest poprawna, false je¿eli nie
*/

bool CSpriteObject::isName(char cName[])
{
	return !strcmp(cName,_cObjectName);
}
	
/**
   Ustawia inkrementatory wspó³rzêdnych.
   
   @param x inkrementator x dla ka¿dej klatki
   @param y inkrementator y dla ka¿dej klatki
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

