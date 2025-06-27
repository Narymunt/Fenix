#include "box.h"

Box::Box()
{
	m_fX1 = 0.0f;	m_fY1 = 0.0f;
	m_fX2 = 0.0f;	m_fY2 = 0.0f;
}

Box::Box(float x1, float y1, float x2, float y2)
{
	m_fX1 = x1; m_fY1 = y1; 
	m_fX2 = x2; m_fY2 = y2;

	update();
}

Box::~Box()
{
}

void Box::set(float x1, float y1, float x2, float y2)
{
	m_fX1 = x1; m_fY1 = y1;
	m_fX2 = x2; m_fY2 = y2;
}

void Box::get(float *x1, float *y1, float *x2, float *y2)
{
	*x1 = m_fX1; *y1 = m_fY1;
	*x2 = m_fX2; *y2 = m_fY2;
}

// sprawdzamy czy 1 to zawsze lewy gorny rog, a 2 to zawsze prawy dolny

void Box::update()
{
	float v;

	if (m_fX1>m_fX2)
	{
		v = m_fX1;
		m_fX1 = m_fX2;
		m_fX2 = v;
	}
	
	if (m_fY1>m_fY2)
	{
		v = m_fY1;
		m_fY1 = m_fY2;
		m_fY2 = v;
	}
	
}

// czy box1 przecina box2

bool Box::isIntersect(Box box1, Box box2)
{
	return false;
}

// czy box1 jest w srodku box2

bool Box::isInside(Box box1, Box box2)
{
	return false;
}

float Box::fX1(void)
{
	return m_fX1;
}

void Box::fX1(float v)
{
	m_fX1 = v;
}

float Box::fY1(void)
{
	return m_fY1;
}

void Box::fY1(float v)
{
	m_fY1 = v;
}

float Box::fX2(void)
{
	return m_fX2;
}

void Box::fX2(float v)
{
	m_fX2 = v;
}

float Box::fY2(void)
{
	return m_fY2;
}

void Box::fY2(float v)
{
	m_fY2 = v;
}

bool Box::sort(void)
{

	return false;
}