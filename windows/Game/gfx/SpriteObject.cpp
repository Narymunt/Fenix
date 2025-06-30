#include "SpriteObject.h"

#pragma warning(disable : 4996)

SpriteObject::SpriteObject() :

_isCenter(false),
_sizeX(0.0f), _sizeY(0.0f),
_rotation(0.0f),
_originalX(0.0f), _originalY(0.0f),
_scaleX(1.0f), _scaleY(1.0f),
_x(0.0f), _y(0.0f),
_pivotX(0.5f), _pivotY(0.5f),
_r(1.0f), _g(1.0f), _b(1.0f), _a(1.0f),

_rotationI(0.0f),
_scaleXI(0.0f), _scaleYI(0.0f),
_xI(0.0f), _yI(0.0f),
_rI(0.0f), _gI(0.0f), _bI(0.0f), _aI(0.0f),

_renderTime(0), _deltaTime(0)

{
	memset(_objectName,0,255);	// nie zawsze ta tablica jest czyszczona
	memset(_fileName,0,255);
}


SpriteObject::~SpriteObject()
{
	memset(_objectName, 0, 255);	// nie zawsze ta tablica jest czyszczona
	memset(_fileName, 0, 255);
}

void SpriteObject::position(float x, float y) { _x = x; _y = y; }
void SpriteObject::positionI(float x, float y) { _xI = x; _yI = y; }

void SpriteObject::scale(float x, float y)
{
	_scaleX = x; _scaleY = y;
	
	_sizeX = _originalX * _scaleX;
	_sizeY = _originalY * _scaleY;
}

void SpriteObject::scale(float s) { scale(s, s); }

void SpriteObject::scaleI(float x, float y) { _scaleXI = x; _scaleYI = y; }
void SpriteObject::scaleI(float s) { scaleI(s, s); }

void SpriteObject::color(float r, float g, float b, float a)
{
	_r = r; _g = g; _b = b; _a = a;
}

void SpriteObject::color(float r, float g, float b)
{
	_r = r; _g = g; _b = b; 
}


void SpriteObject::colorI(float r, float g, float b, float a)
{
	_rI = r; _gI = g; _bI = b; _aI = a;
}

void SpriteObject::pivot(float x, float y) { _pivotX = x; _pivotY = y; }

void SpriteObject::resize(int x1, int y1, int x2, int y2) 
{
	position((float)x1, (float)y1);
	scale((float)(x2 - x1) / (float)(_originalX), (float)(y2 - y1) / (float)(_originalY));
}

void SpriteObject::fullscreen(Screen *screen) 
{ 
	resize(0, 0, screen->_sizeX, screen->_sizeY); 
}

bool SpriteObject::isName(char name[]) 
{ 
	return !strcmp(name,_objectName); 
}
	

