#include "box.h"

CBox::CBox()
{
	m_fX1 = 0.0f;	m_fY1 = 0.0f;
	m_fX2 = 0.0f;	m_fY2 = 0.0f;
}

CBox::CBox(float x1, float y1, float x2, float y2)
{
	m_fX1 = x1; m_fY1 = y1; 
	m_fX2 = x2; m_fY2 = y2;

	update();
}

CBox::~CBox()
{
}

void CBox::set(float x1, float y1, float x2, float y2)
{
	m_fX1 = x1; m_fY1 = y1;
	m_fX2 = x2; m_fY2 = y2;
}

void CBox::get(float *x1, float *y1, float *x2, float *y2)
{
	x1 = m_fX1; y1 = m_fY1;
	x2 = m_fX2; y2 = m_fY2;
}

// sprawdzamy czy 1 to zawsze lewy gorny rog, a 2 to zawsze prawy dolny

void CBox::update()
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

bool CBox::isIntersect(CBox box1, CBox box2)
{

}

// czy box1 jest w srodku box2

bool CBox::isInside(CBox box1, CBox box2)
{

}

float CBox::fX1(void)
{
	return m_fX1;
}

void CBox::fX1(float v)
{
	m_fX1 = v;
}

float CBox::fY1(void)
{
	return m_fY1;
}

void CBox::fY1(float v)
{
	m_fY1 = v;
}

float CVBox::fX2(void)
{
	return m_fX2;
}

void CBox::fX2(float v)
{
	m_fX2 = v;
}

float CBox::fY2(void)
{
	return m_fY2;
}

void CBox::fY2(float v)
{
	m_fY2 = v;
}
