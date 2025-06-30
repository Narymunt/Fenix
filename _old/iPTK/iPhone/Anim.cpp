// main class

#include "Anim.h"

// konstruktor, tutaj pakujemy najmniej jak tylko możliwe

CAnim::CAnim(char cFilename[], int iCount, int iSizeX, int iSizeY)
{
    char cName[200];
    

    for (unsigned long i=0; i<=iCount; i++)
    {
        if (i<10) sprintf(cName,"%s000%lu.png",cFilename,i);
        if (i>9 && i<100) sprintf(cName,"%s00%lu.png",cFilename,i);
        if (i>99 && i<1000) sprintf(cName,"%s0%lu.png",cFilename,i);

        m_pAnimation.push_back(new CSprite(cName,0,0,iSizeX,iSizeY));
        
    }
    
    m_fAngle = 0.0f;
    m_fAlfa = 1.0f;
    m_fScale = 1.0f;
    
    m_iCount = iCount;  // zapamietaj liczbe klatek
    
}

CAnim::~CAnim()
{
    m_pAnimation.clear();       // usuwa wszystko z wektora
}

void CAnim::Render(int iFrame)
{
    m_pAnimation[iFrame]->SetPosition(m_fX, m_fY);
    m_pAnimation[iFrame]->SetRotation(m_fAngle);
    m_pAnimation[iFrame]->Render();    
}


void CAnim::Render(int iX, int iY, int iFrame)
{
    if (iFrame > m_iCount) iFrame %= m_iCount;
        
    m_pAnimation[iFrame]->SetPosition((float)iX, (float)iY);
    m_pAnimation[iFrame]->SetRotation(m_fAngle);
    m_pAnimation[iFrame]->Render();
}


// ustawianie kąta

void CAnim::SetRotation(float fAngle)
{
    m_fAngle = fAngle;
}

// zwraca kąta

float CAnim::fGetRotation(void)
{
    return m_fAngle;
}

// ustawianie alfy

void CAnim::SetAlfa(float fAlfa)
{
    m_fAlfa = fAlfa;
}

float CAnim::fGetAlfa(void)
{
    return m_fAlfa;
}

void CAnim::SetPosition(float fX, float fY)
{
    m_fX = fX;
    m_fY = fY;
}

void CAnim::AddPosition(float fAddX, float fAddY)
{
    m_fX += fAddX;
    m_fY += fAddY;    
}

void CAnim::SetPositionX(float fX)
{
    m_fX = fX;
}

void CAnim::SetPositionY(float fY)
{
    m_fY = fY;
}

float CAnim::fGetX(void)
{
    return m_fX;
}

float CAnim::fGetY(void)
{
    return m_fY;
}

void CAnim::SetScale(float fScale)
{
    m_fScale = fScale;
}

float CAnim::fGetScale(void)
{
    return m_fScale;
}

void CAnim::SetVisible (bool bState)
{
    m_bVisible = bState;
}

bool CAnim::bGetVisible(void)
{
    return m_bVisible;
}

// zwraca liczbe klatek

int CAnim::iGetFrameCount(void)
{
    return m_iCount;    
}
