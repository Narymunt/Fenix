#include "vector2D.h"

CVector2D::CVector2D(float x, float y)
{	m_fX = x; 	m_fY = y;
	m_fX1 = 0.0f;	m_fY1 = 0.0f;	m_fX2 = 0.0f;	m_fY2 = 0.0f;}

CVector2D::CVector2D(float x1, float y1, float x2, float y2)
{
	m_fX1 = x1; m_fY1 = y1; 
	m_fX2 = x2; m_fY2 = y2;
}

CVector2D::~CVector2D()
{

}

void CVector2D::set(float nx, float ny)
{
	m_fX = nx;
	m_fY = ny;
}

void CVector2D::set(float x1, float y1, float x2, float y2)
{
	m_fX1 = x1; m_fY1 = y1;
	m_fX2 = x2; m_fY2 = y2;
}

void CVector2D::get(float *nx, float *ny)
{
	nx = m_fX; 
	ny = m_fY;
}

void CVector2D::get(float *x1, float *y1, float *x2 float *y2)
{
	x1 = m_fX1; y1 = m_fY1;
	x2 = m_fX2; y2 = m_fY2;
}

float CVector2D::fX(void)
{
	return m_fX;
}

void CVector2D::fX(float v)
{
	m_fX = v;
}

float CVector2D::fY(void)
{
	return m_fY;
}

void CVector2D::fY(float v)
{
	m_fY = v;
}

float CVector2D::fX1(void)
{
	return m_fX1;
}

void CVector2D::fX1(float v)
{
	m_fX1 = v;
}

float CVector2D::fY1(void)
{
	return m_fY1;
}

void CVector2D::fY1(float v)
{
	m_fY1 = v;
}

float CVector2D::fX2(void)
{
	return m_fX2;
}

void CVector2D::fX2(float v)
{
	m_fX2 = v;
}

float CVector2D::fY2(void)
{
	return m_fY2;
}

void CVector2D::fY2(float v)
{
	m_fY2 = v;
}





