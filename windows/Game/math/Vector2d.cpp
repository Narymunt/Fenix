#include "vector2D.h"

Vector2D::Vector2D(float x, float y)
{
	_fX = x; 
	_fY = y;
	_fX1 = 0.0f;	_fY1 = 0.0f;
	_fX2 = 0.0f;	_fY2 = 0.0f;
}

Vector2D::Vector2D(float x1, float y1, float x2, float y2)
{
	_fX1 = x1; _fY1 = y1; 
	_fX2 = x2; _fY2 = y2;
}

Vector2D::~Vector2D()
{

}

void Vector2D::set(float nx, float ny)
{
	_fX = nx;
	_fY = ny;
}

void Vector2D::set(float x1, float y1, float x2, float y2)
{
	_fX1 = x1; _fY1 = y1;
	_fX2 = x2; _fY2 = y2;
}

void Vector2D::get(float *nx, float *ny)
{
	*nx = _fX; 
	*ny = _fY;
}

void Vector2D::get(float *x1, float *y1, float *x2, float *y2)
{
	*x1 = _fX1; *y1 = _fY1;
	*x2 = _fX2; *y2 = _fY2;
}

float Vector2D::fX(void)
{
	return _fX;
}

void Vector2D::fX(float v)
{
	_fX = v;
}

float Vector2D::fY(void)
{
	return _fY;
}

void Vector2D::fY(float v)
{
	_fY = v;
}

float Vector2D::fX1(void)
{
	return _fX1;
}

void Vector2D::fX1(float v)
{
	_fX1 = v;
}

float Vector2D::fY1(void)
{
	return _fY1;
}

void Vector2D::fY1(float v)
{
	_fY1 = v;
}

float Vector2D::fX2(void)
{
	return _fX2;
}

void Vector2D::fX2(float v)
{
	_fX2 = v;
}

float Vector2D::fY2(void)
{
	return _fY2;
}

void Vector2D::fY2(float v)
{
	_fY2 = v;
}





