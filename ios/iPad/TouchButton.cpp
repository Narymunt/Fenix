// Touch button class

#include "TouchButton.h"

// konstruktor, tutaj pakujemy najmniej jak tylko możliwe

CTouchButton::CTouchButton(int iX1, int iY1, int iX2, int iY2, char cIdle[], char cOnOver[],char cOnClick[]) :
_isPressed(false)
{
    m_cType = 3;    // 3 plikowy przycisk
    
    m_pIdle = new CSprite(cIdle,0,0,iX2,iY2);   
    m_pIdle->SetPosition((float)iX1, (float)iY1);
    
    m_pOnOver = new CSprite(cOnOver,0,0,iX2, iY2);
    m_pOnOver->SetPosition((float)iX1, (float)iY1);
    
    m_pOnClick = new CSprite(cOnClick,0,0,iX2, iY2);
    m_pOnClick->SetPosition((float)iX1, (float)iY1);

    m_iX = iX1; m_iY = iY1;     // wspolrzedne na ekranie
    
    m_iXSize = iX2-iX1;
    m_iYSize = iY2-iY1; // rozmiar przycisku

    m_iHotX1 = iX1;
    m_iHotY1 = iY1;

    m_iHotX2 = iX1+iX2;
    m_iHotY2 = iY1+iY2;
    
    
    
    m_bActive = true;
}

CTouchButton::CTouchButton(int iX1, int iY1, int iX2, int iY2, 
             int iU1, int iV1, int iDU1, int iDV1, 
             int iU2, int iV2, int iDU2, int iDV2, 
             int iU3, int iV3, int iDU3, int iDV3,
                           char cTexture[]) :
_isPressed(false)
{
    m_cType = 1; 
    
    m_pTexture = new CSprite(cTexture,iU1,iV1,iDU1,iDV1);
    m_pTexture->SetPosition((float)iX1,(float)iY1);
    
    m_iX = iX1; m_iY = iY1; 

    m_iXSize = iX2-iX1;
    m_iYSize = iY2-iY1; // rozmiar przycisku
    
    m_iHotX1 = iX1;
    m_iHotY1 = iY1;
    
    m_iHotX2 = iX1+iX2;
    m_iHotY2 = iY1+iY2;
    
    m_iU1 = iU1; m_iV1 = iV1; m_iDU1 = iDU1; m_iDV1 = iDV1;
    m_iU2 = iU2; m_iV2 = iV2; m_iDU2 = iDU2; m_iDV2 = iDV2;
    m_iU3 = iU3; m_iV3 = iV3; m_iDU3 = iDU3; m_iDV3 = iDV3;   
    
    m_bActive = true;
    
}

CTouchButton::~CTouchButton()
{
    if (m_cType==3)
    {
        SafeDelete(m_pIdle);
        SafeDelete(m_pOnOver);
        SafeDelete(m_pOnClick);        
    }
    
    if (m_cType==1)
    {
        SafeDelete(m_pTexture);
    }

    m_bActive = false;
    
}

int CTouchButton::Render(CTouch *pTouch)
{
    if (m_cType==3)
    {
        if (pTouch->iGetX() > m_iX && pTouch->iGetX() < (m_iX+m_iXSize) && 
            pTouch->iGetY() > m_iY && pTouch->iGetY() < (m_iY+m_iYSize))
        {
            if (pTouch->isReleased() && _isPressed)
            {
                m_pOnClick->Render();
                return 10;
            }
            
            if (pTouch->isPressed())
            {
                _isPressed = true;
                m_pOnOver->Render();
                return 40;
            }
        }
       
        _isPressed = false;
       m_pIdle->Render();
    }
    
    if (m_cType==1)
    {

        if (pTouch->iGetX() > m_iX && pTouch->iGetX() < (m_iX+m_iXSize) && 
            pTouch->iGetY() > m_iY && pTouch->iGetY() < (m_iY+m_iYSize))
        {
            if (pTouch->isReleased())
            {
                m_pTexture->SetTexture(m_iU3, m_iV3, m_iDU3, m_iDV3);
                m_pTexture->Render();
                return 10;
            }
            
            if (pTouch->isPressed())
            {
                m_pTexture->SetTexture(m_iU2, m_iV2, m_iDU2, m_iDV2);
                m_pTexture->Render();
                return 40;
            }
        }
        
        
        m_pTexture->SetTexture(m_iU1, m_iV1, m_iDU1, m_iDV1);   // ustaw nowe wspolrzedne U,V
        m_pTexture->Render();
        
    }
    
    
    return 0;
}

void CTouchButton::SetPosition(int iX1, int iY1)
{
    m_iX = iX1;
    m_iY = iY1;

    m_iHotX1 = m_iX; m_iHotY1 = m_iY;

    m_iHotX2 = m_iX + m_iXSize;
    m_iHotY2 = m_iY + m_iYSize;
    
    if (m_cType==3)
    {
        m_pIdle->SetPosition((float)iX1,(float)iY1);
        m_pOnOver->SetPosition((float)iX1,(float)iY1);
        m_pOnClick->SetPosition((float)iX1,(float)iY1);         
    }
    
    if (m_cType==1)
    {
        m_pTexture->SetPosition((float)iX1, (float)iY1);
    }
}

void CTouchButton::SetSize(int iXSize, int iYSize)
{
    m_iXSize = iXSize;
    m_iYSize = iYSize;
}

void CTouchButton::SetHotCoords(int iX1, int iY1, int iX2, int iY2)
{
    m_iHotX1 = iX1; m_iHotY1 = iY1;
    m_iHotX2 = iX1; m_iHotY2 = iY1;    
}

void CTouchButton::SetUV(int iU1, int iV1, int iDU1, int iDV1, 
           int iU2, int iV2, int iDU2, int iDV2, 
           int iU3, int iV3, int iDU3, int iDV3)
{
    m_iU1 = iU1; m_iV1 = iV1;
    m_iU2 = iU2; m_iV2 = iV2;
    m_iU3 = iU3; m_iV3 = iV3;   
}

bool CTouchButton::isActive(void)
{
    return m_bActive;
}

