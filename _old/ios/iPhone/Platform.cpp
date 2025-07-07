// main class

#include "Platform.h"

// konstruktor, tutaj pakujemy najmniej jak tylko możliwe

CPlatform::CPlatform(char cFilename[], float fX, float fY, float fSizeX, float fSizeY)
{
    m_pImage = new CSprite(cFilename,0,0,256,256);
    
    m_fX = fX; 
    m_fY = fY;
    
    m_fIncX = 0.0f;
    m_fIncY = 0.0f;
        
    m_fSizeX = fSizeX;
    m_fSizeY = fSizeY;
    
    m_pBoundBox = new CBox(fX,fY,fX+fSizeX,fY+fSizeY);
    
    m_bActive = true;
    
}

CPlatform::~CPlatform()
{
    if (m_bActive)
    {        
        SafeDelete(m_pImage);
        SafeDelete(m_pBoundBox);
        m_bActive = false;
    }    
}

int CPlatform::Render(CTouch *pTouch, unsigned long ulTimer)
{    
 
    m_pBoundBox->Update(m_fX, m_fY, m_fX+m_fSizeX, m_fY+m_fSizeY);
    m_pImage->Render(m_fX, m_fY);         
    
    m_fX += m_fIncX;
    m_fY += m_fIncY;         
    
    return 0;   // nie rob nic
}

bool CPlatform::isActive(void)
{
    return m_bActive;
}

float CPlatform::fGetForceX(void)
{
    return m_fIncX;    
}

float CPlatform::fGetForceY(void)
{
    return m_fIncY;
}

CBox *CPlatform::eGetBBox(void)
{
    return m_pBoundBox;
}
