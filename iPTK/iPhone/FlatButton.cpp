// Touch button class

#include "FlatButton.h"

// konstruktor, tutaj pakujemy najmniej jak tylko możliwe

CFlatButton::CFlatButton(int iX1, int iY1, int iX2, int iY2, char cTexture[])
{   
    m_pTexture = new CSprite(cTexture,0,0,iX2,iY2);   
    m_pTexture->SetPosition((float)iX1, (float)iY1);

    m_iX = iX1; m_iY = iY1;     // wspolrzedne na ekranie
    
    m_iXSize = iX2; m_iYSize = iY2; // rozmiar przycisku        

    m_iHotX1 = iX1; m_iHotY1 = iY1;

    m_iHotX2 = iX1+iX2;
    m_iHotY2 = iY1+iY2;        
    
    m_iU1 = iX1; m_iV1 = iY1;
    m_iU2 = iX2; m_iV2 = iY2;   
    
    m_bActive = true;
}

CFlatButton::CFlatButton(int iX1, int iY1, int iX2, int iY2, 
             int iU1, int iV1, int iU2, int iV2, 
             char cTexture[])
{    
    m_pTexture = new CSprite(cTexture,iU1,iV1,iU2,iV2);
    m_pTexture->SetPosition((float)iX1,(float)iY1);
    
    m_iX = iX1; m_iY = iY1; 

    m_iXSize = iX2; m_iYSize = iY2; // rozmiar przycisku        
    
    m_iHotX1 = iX1; m_iHotY1 = iY1;
    
    m_iHotX2 = iX1+iX2;
    m_iHotY2 = iY1+iY2;
    
    m_iU1 = iU1; m_iV1 = iV1; m_iU2 = iU2; m_iV2 = iV2;
    
    m_bActive = true;
    
}

CFlatButton::~CFlatButton()
{
    SafeDelete(m_pTexture);
    m_bActive = false;    
}

// render przycisku zwraca tylko dwa stany
// 0 = przycisk nie wcisniety
// 1 = przycisk wcisniety

int CFlatButton::Render(CTouch *pTouch)
{

    m_pTexture->SetTexture(m_iU1, m_iV1, m_iU2, m_iV2);   // ustaw nowe wspolrzedne U,V
    m_pTexture->Render(m_iX, m_iY);
    
    if (pTouch->iGetX() > m_iX && pTouch->iGetX() < (m_iX+m_iXSize) && 
        pTouch->iGetY() > m_iY && pTouch->iGetY() < (m_iY+m_iYSize) && 
        pTouch->isPressed())
    {
        return 1;   
    }

    return 0;
}

int CFlatButton::Render(CTouch *pTouch, int iX, int iY)
{
    m_iX = iX; m_iY = iY;
    m_pTexture->SetTexture(m_iU1, m_iV1, m_iU2, m_iV2);   // ustaw nowe wspolrzedne U,V
    m_pTexture->Render(m_iX, m_iY);
    
    if (pTouch->iGetX() > m_iX && pTouch->iGetX() < (m_iX+m_iXSize) && 
        pTouch->iGetY() > m_iY && pTouch->iGetY() < (m_iY+m_iYSize) && 
        pTouch->isPressed())
    {
        return 1;   
    }
    
    return 0;
}


void CFlatButton::SetPosition(int iX1, int iY1)
{
    m_iX = iX1; m_iY = iY1;

    m_pTexture->SetPosition((float)iX1,(float)iY1);
        
}

void CFlatButton::SetSize(int iXSize, int iYSize)
{
    m_iXSize = iXSize;
    m_iYSize = iYSize;
}

void CFlatButton::SetHotCoords(int iX1, int iY1, int iX2, int iY2)
{
    m_iHotX1 = iX1; m_iHotY1 = iY1;
    m_iHotX2 = iX1; m_iHotY2 = iY1;    
}

void CFlatButton::SetUV(int iU1, int iV1, int iU2, int iV2)
{
    m_iU1 = iU1; m_iV1 = iV1;
    m_iU2 = iU2; m_iV2 = iV2;
}

bool CFlatButton::isActive(void)
{
    return m_bActive;
}

