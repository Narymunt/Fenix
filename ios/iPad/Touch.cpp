// main class

#include <stdio.h>
#include "Touch.h"

// konstruktor, tutaj pakujemy najmniej jak tylko możliwe

CTouch::CTouch() :
_iStartX(0), _iStartY(0), _fClickDeltaX(0), _fClickDeltaY(0)
{
    m_bPressed = false;
    m_bReleased = false;
    m_iX = 0; 
    m_iY = 0;
    m_iTap = 0;
}

// destruktor, nie ma zmiennych do zwolnienia

CTouch::~CTouch()
{
}

void CTouch::Update(bool bPressed, bool bReleased, int iX, int iY, int iTap)
{
    m_bPressed = bPressed;
    m_bReleased = bReleased;
    
    m_iX = iX;
    m_iY = iY;

    m_iTap = iTap;
    
    if (bReleased)
    {
        _iStartX = 0;
        _iStartY = 0;
        
        _fClickDeltaX = 0.0f;
        _fClickDeltaY = 0.0f;
    }

    if (bPressed)
    {
        if (_iStartX==0 && _iStartY==0)
        {
            _iStartX = m_iX;
            _iStartY = m_iY;
        }
        
        _fClickDeltaX = m_iX - _iStartX;
        _fClickDeltaY = m_iY - _iStartY;
    }
}

bool CTouch::isPressed(void)
{
    return m_bPressed;
}

bool CTouch::isReleased(void)
{
    return m_bReleased;
}

int CTouch::iGetX(void)
{
    return m_iX;
}

int CTouch::iGetY(void)
{
    return m_iY;
}

int CTouch::iGetTap()
{
    return m_iTap;
}

void CTouch::Reset()
{
    m_iX = 0;
    m_iY = 0;
}