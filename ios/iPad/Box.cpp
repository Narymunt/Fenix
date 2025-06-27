// main class

#include "Box.h"

// konstruktor, tutaj pakujemy najmniej jak tylko możliwe

CBox::CBox(float fx1, float fy1, float fx2, float fy2)
{
    m_fx1 = fx1; 
    m_fy1 = fy1;
    m_fx2 = fx2; 
    m_fy2 = fy2;
}

CBox::~CBox()
{
    
}

void CBox::Update(float fx1, float fy1, float fx2, float fy2)
{
    m_fx1 = fx1; 
    m_fy1 = fy1;
    m_fx2 = fx2; 
    m_fy2 = fy2;
    
}