#include "SpriteObject.h"

#pragma warning(disable : 4996)

CSpriteObject::CSpriteObject(char cObjectName[], int iX, int iY, char cFilename[])
{
	memset(_cObjectName,0,255);	// nie zawsze ta tablica jest czyszczona
	memset(_cFilename,0,255);

	strcpy(_cObjectName, cObjectName);
	strcpy(_cFilename, cFilename);
}

// destructor

CSpriteObject::~CSpriteObject()
{
	
}

void CSpriteObject::fRotation(float fRot)
{
	_fRotation = fRot;
}
	
float CSpriteObject::fRotation(void)
{
	return _fRotation;
}

// set & get position

void CSpriteObject::Position(float fX, float fY)
{
	_fPositionX = fX;
	_fPositionY = fY;
}

float CSpriteObject::fPositionX(void)
{
	return _fPositionX;
}

void CSpriteObject::fPositionX(float fX)
{
	_fPositionX = fX;
}

float CSpriteObject::fPositionY(void)
{
	return _fPositionY;
}

void CSpriteObject::fPositionY(float fY)
{
	_fPositionY = fY;
}

// set & get scale, update size

void CSpriteObject::Scale(float fX, float fY)
{
	_fScaleX = fX;
	_fScaleY = fY;
}

void CSpriteObject::fScaleX(float fX)
{
	_fScaleX = fX;
}

float CSpriteObject::fScaleX(void)
{
	return _fScaleX;
}

void CSpriteObject::fScaleY(float fY)
{
	_fScaleY = fY;
}

float CSpriteObject::fScaleY(void)
{
	return _fScaleY;
}

// set & get alfa

void CSpriteObject::fAlfa(float f)
{
	_fAlfa = f;
}

float CSpriteObject::fAlfa(void)
{
	return _fAlfa;
}

bool CSpriteObject::isName(char cName[])
{
	return !strcmp(cName,_cObjectName);
}
	
void CSpriteObject::PositionI(float x, float y)
{ 
	_fPositionXI = x; 
	_fPositionYI = y; 
}

void CSpriteObject::ScaleI(float x, float y)
{
	_fScaleXI = x;
	_fScaleYI = y;
}

