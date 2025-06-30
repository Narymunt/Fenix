// sprite class

#include "Sprite.h"

// konstruktor, tutaj pakujemy najmniej jak tylko możliwe

CSprite::CSprite()
{
    m_bVisible = false; // na razie bez obrazu więc nie renderujemy

    m_fAngle = 0.0f;
    m_fScale = 1.0f;
    m_fAlfa = 1.0f;
    m_fX = 0.0f;
    m_fY = 0.0f;
    
    m_iX1 = 0;
    m_iY1 = 0;
    m_iX2 = 0;
    m_iY2 = 0;  
    
}

// konstruktor z inicjalizacją

CSprite::CSprite(char cFilename[], int x1, int y1, int x2, int y2)
{
    m_pImage = KPTK::createKGraphic();
	m_pImage->loadPicture(cFilename);	
   
    m_fAngle = 0.0f;
    m_fScale = 1.0f;
    m_fAlfa = 1.0f;
    m_fX = 0.0f;
    m_fY = 0.0f;  
    
    // wspolrzedne na teksturze
    
    m_iX1 = x1; 
    m_iY1 = y1; 
    m_iX2 = x2; 
    m_iY2 = y2; 
    
    m_bVisible = true;  // bedzie renderowany w kolejce
}

// destruktor

CSprite::~CSprite()
{
    SafeDelete(m_pImage);    
    m_bVisible = false;
    
}

// renderowanie na ekranie

void CSprite::Render(void)
{
    if (m_bVisible)
    {
        m_pImage->blitAlphaRectFx(m_iX1, m_iY1, m_iX2, m_iY2, m_fX, m_fY, m_fAngle, m_fScale, m_fAlfa);         
    }

}

void CSprite::Render(float fX, float fY)
{
    SetPosition(fX,fY);

    if (m_bVisible)
    {
        m_pImage->blitAlphaRectFx(m_iX1, m_iY1, m_iX2, m_iY2, m_fX, m_fY, m_fAngle, m_fScale, m_fAlfa);         
    }
    
}

void CSprite::Render(float fX, float fY, float fAlpha, float fAngle)
{
    SetPosition(fX,fY);
    SetAlfa(fAlpha);
    SetRotation(fAngle);
    Render();
}


// ustawianie kąta

void CSprite::SetRotation(float fAngle)
{
    m_fAngle = fAngle;
}

// zwraca kąta

float CSprite::fGetRotation(void)
{
    return m_fAngle;
}

// ustawianie alfy

void CSprite::SetAlfa(float fAlfa)
{
    m_fAlfa = fAlfa;
}

float CSprite::fGetAlfa(void)
{
    return m_fAlfa;
}

void CSprite::SetPosition(float fX, float fY)
{
    m_fX = fX;
    m_fY = fY;
}

void CSprite::AddPosition(float fAddX, float fAddY)
{
    m_fX += fAddX;
    m_fY += fAddY;    
}

void CSprite::SetPositionX(float fX)
{
    m_fX = fX;
}

void CSprite::SetPositionY(float fY)
{
    m_fY = fY;
}

float CSprite::fGetX(void)
{
    return m_fX;
}

float CSprite::fGetY(void)
{
    return m_fY;
}

void CSprite::SetScale(float fScale)
{
    m_fScale = fScale;
}

float CSprite::fGetScale(void)
{
    return m_fScale;
}

void CSprite::SetVisible (bool bState)
{
    m_bVisible = bState;
}

bool CSprite::bGetVisible(void)
{
    return m_bVisible;
}

void CSprite::SetTexture(int x1, int y1, int x2, int y2)
{
    m_iX1 = x1; 
    m_iY1 = y1; 
    m_iX2 = x2; 
    m_iY2 = y2;
}

int CSprite::iGetTextureX1(void)
{
    return m_iX1;
}

int CSprite::iGetTextureY1(void)
{
    return m_iY1;
}

int CSprite::iGetTextureX2(void)
{
    return m_iX2;
}

int CSprite::iGetTextureY2(void)
{
    return m_iY2;
}

